# -*- coding: utf-8 -*-
"""Gera o .docx de um roteiro a partir do Markdown, com a capa igual à do Roteiro 1.

O Markdown é a fonte. Tudo antes da primeira linha horizontal (---) é tratado como
capa: em vez de converter esse trecho, o script copia os parágrafos da capa do docx
de referência (centralizados, com os espaçamentos do modelo) e troca só o título da
etapa. O resto vira docx pelo pandoc, com os estilos do mesmo docx de referência.

Uso:
  python3 tools/gerar_docx.py <roteiro.md> <saida.docx> <referencia.docx> "<título da etapa>"
"""
import os
import re
import subprocess
import sys
import tempfile
import zipfile

CAPA_REF = "Diagnóstico e teorização"  # título da etapa na capa do docx de referência


def capa_xml(referencia, titulo):
    doc = zipfile.ZipFile(referencia).read("word/document.xml").decode("utf-8")
    body = doc[doc.index("<w:body>") + len("<w:body>"):]
    paragrafos = re.findall(r"<w:p[ >].*?</w:p>", body, re.S)
    capa = []
    for p in paragrafos:
        if 'w:val="Heading1"' in p:  # a capa termina onde começa o primeiro título
            break
        capa.append(p)
    xml = "".join(capa).replace(CAPA_REF, titulo)
    # o docx do pandoc não declara o namespace w14 nem conhece os marcadores do Word;
    # copiados como estão, deixam o XML inválido e o Word se recusa a abrir
    xml = re.sub(r'\s+w14:\w+="[^"]*"', "", xml)
    xml = re.sub(r"<w:bookmark(?:Start|End)[^>]*/>", "", xml)
    return xml + '<w:p><w:r><w:br w:type="page"/></w:r></w:p>'


def bordas_nas_tabelas(docx):
    """O docx de referência não tem estilo de tabela com borda, e sem borda as tabelas
    viram colunas soltas no PDF. Põe grade fina preta, cabeçalho em negrito com fundo cinza."""
    tmp = docx + ".tmp"
    with zipfile.ZipFile(docx) as zin, zipfile.ZipFile(tmp, "w", zipfile.ZIP_DEFLATED) as zout:
        for item in zin.infolist():
            dados = zin.read(item.filename)
            if item.filename == "word/document.xml":
                xml = dados.decode("utf-8")
                borda = "".join(f'<w:{b} w:val="single" w:sz="4" w:space="0" w:color="000000"/>'
                                for b in ("top", "left", "bottom", "right", "insideH", "insideV"))
                # o Word exige ordem fixa dos filhos de tblPr e tcPr; fora dela ele pede
                # para "recuperar conteúdo". Por isso insere antes do primeiro elemento
                # que precisa vir depois, e não no começo do bloco.
                def inserir(bloco, novo, depois_de):
                    for tag in depois_de:
                        i = bloco.find("<w:" + tag)
                        if i != -1:
                            return bloco[:i] + novo + bloco[i:]
                    fim = bloco.rindex("</")
                    return bloco[:fim] + novo + bloco[fim:]

                xml = re.sub(r"<w:tblPr>.*?</w:tblPr>",
                             lambda m: inserir(re.sub(r"<w:tblBorders>.*?</w:tblBorders>", "", m.group(0)),
                                               f"<w:tblBorders>{borda}</w:tblBorders>",
                                               ("shd", "tblLayout", "tblCellMar", "tblLook", "tblCaption")),
                             xml, flags=re.S)
                sombra = '<w:shd w:val="clear" w:color="auto" w:fill="E7E9EE"/>'

                def cabecalho(m):
                    linha = m.group(2).replace("<w:tcPr />", "<w:tcPr></w:tcPr>")
                    linha = re.sub(r"<w:tcPr>.*?</w:tcPr>",
                                   lambda t: inserir(t.group(0), sombra, ("noWrap", "tcMar", "textDirection", "tcFitText", "vAlign", "hideMark")),
                                   linha, flags=re.S)
                    linha = re.sub(r"<w:r>(?!<w:rPr>)", "<w:r><w:rPr><w:b/></w:rPr>", linha)
                    return m.group(1) + linha
                xml = re.sub(r"(<w:tbl>.*?)(<w:tr[ >].*?</w:tr>)", cabecalho, xml, flags=re.S)
                dados = xml.encode("utf-8")
            zout.writestr(item, dados)
    os.replace(tmp, docx)


def main(md, saida, referencia, titulo):
    texto = open(md, encoding="utf-8").read()
    corpo = texto.split("\n---\n", 1)[1]
    base = os.path.dirname(os.path.abspath(md))
    # figuras: o docx recebe o PNG; a legenda já vem no texto ("Figura N – ..."),
    # então o alt vira vazio para o pandoc não repetir legenda embaixo da imagem
    corpo = re.sub(r"!\[[^\]]*\]\(([^)]+)\.svg\)", r"![](\1.png)", corpo)
    with tempfile.TemporaryDirectory() as tmp:
        lua = os.path.join(tmp, "capa.lua")
        cap = os.path.join(tmp, "capa.xml")
        open(cap, "w", encoding="utf-8").write(capa_xml(referencia, titulo))
        open(lua, "w", encoding="utf-8").write(
            'local f = io.open("%s"); local capa = f:read("a"); f:close()\n'
            "function Pandoc(doc)\n"
            "  table.insert(doc.blocks, 1, pandoc.RawBlock('openxml', capa))\n"
            "  return doc\n"
            "end\n" % cap.replace("\\", "/"))
        src = os.path.join(tmp, "corpo.md")
        open(src, "w", encoding="utf-8").write(corpo)
        subprocess.run(["pandoc", src, "-o", saida, "--reference-doc", referencia,
                        "--resource-path", base, "--lua-filter", lua], check=True)
    bordas_nas_tabelas(saida)
    print("ok", saida)


if __name__ == "__main__":
    main(*sys.argv[1:5])
