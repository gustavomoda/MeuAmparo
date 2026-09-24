# -*- coding: utf-8 -*-
"""Gera o Gantt do Roteiro 2 a partir do quadro do GitHub (Project 2).

O quadro é a fonte do cronograma: cada issue tem Frente, Start date, Target date e
responsáveis. Este script lê isso com o gh, desenha uma faixa por frente e marca as
entregas (milestones) como linhas verticais. SVG escrito à mão, sem dependência além
do gh, para rodar em qualquer máquina do grupo.

Uso: python3 tools/gantt.py docs/projeto/01-entregas/figuras/gantt_cronograma.svg
"""
import json
import subprocess
import sys
from datetime import date, timedelta

OWNER, PROJETO, REPO = "gustavomoda", "2", "gustavomoda/MeuAmparo"
FRENTES = ["Parte interessada", "Hardware", "Firmware", "Backend", "Documentação"]
CORES = {
    "Parte interessada": "#3f6493",
    "Hardware": "#6f4f96",
    "Firmware": "#2b7f63",
    "Backend": "#8a5a2b",
    "Documentação": "#7a7a7a",
}
NOMES = {"gustavomoda": "Gustavo", "isabellyvcabral": "Isa"}


def gh(*args):
    return json.loads(subprocess.run(["gh", *args], capture_output=True, text=True, check=True).stdout)


def dia(s):
    return date.fromisoformat(s[:10])


def tarefas():
    itens = gh("project", "item-list", PROJETO, "--owner", OWNER, "--format", "json", "--limit", "100")["items"]
    out = []
    for it in itens:
        # itens arquivados não vêm na lista; os sem data não entram no cronograma
        if not it.get("start date") or not it.get("target date") or not it.get("frente"):
            continue
        quem = " e ".join(NOMES.get(a, a) for a in (it.get("assignees") or [])) or "a definir"
        out.append((it["frente"], it["content"]["number"], it["title"], dia(it["start date"]), dia(it["target date"]), quem))
    out.sort(key=lambda t: (FRENTES.index(t[0]), t[3], t[1]))
    return out


def marcos():
    ms = gh("api", f"repos/{REPO}/milestones?state=all")
    return sorted((dia(m["due_on"]), m["title"]) for m in ms if m.get("due_on"))


def svg(linhas, entregas, destino):
    ini = min(t[3] for t in linhas)
    fim = max(max(t[4] for t in linhas), max(d for d, _ in entregas))
    ini -= timedelta(days=ini.weekday() - 2 if ini.weekday() >= 2 else ini.weekday() + 5)  # começa numa quarta, dia de aula
    dias = (fim - ini).days + 3
    ESQ, DIR, TOPO, BASE, ALT, BARRA, LARG = 480, 110, 120, 64, 30, 18, 1150
    area = LARG - ESQ - DIR
    alt_total = TOPO + len(linhas) * ALT + BASE
    x = lambda d: ESQ + area * (d - ini).days / dias
    esc = lambda s: s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
    p = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{LARG}" height="{alt_total}" viewBox="0 0 {LARG} {alt_total}" font-family="Arial, Helvetica, sans-serif">',
         f'<rect width="{LARG}" height="{alt_total}" fill="#fff"/>',
         f'<text x="{LARG/2:.0f}" y="30" text-anchor="middle" font-size="22" font-weight="bold" fill="#1a1a1a">MeuAmparo — cronograma do projeto</text>']
    # faixas por frente
    y, i = TOPO, 0
    for n, f in enumerate(FRENTES):
        qtd = sum(1 for t in linhas if t[0] == f)
        if not qtd:
            continue
        if n % 2 == 0:
            p.append(f'<rect x="8" y="{y}" width="{LARG-DIR-8+60}" height="{qtd*ALT}" fill="#f3f4f7"/>')
        p.append(f'<text x="14" y="{y + qtd*ALT/2 + 5:.0f}" font-size="14" font-weight="bold" fill="{CORES[f]}">{esc(f)}</text>')
        y += qtd * ALT
    # grade semanal
    d = ini
    while d <= fim + timedelta(days=2):
        gx = x(d)
        p.append(f'<line x1="{gx:.1f}" y1="{TOPO-8}" x2="{gx:.1f}" y2="{alt_total-BASE+4}" stroke="#d6d9e0"/>')
        p.append(f'<text x="{gx:.1f}" y="{alt_total-BASE+20}" text-anchor="middle" font-size="12" fill="#555">{d:%d/%m}</text>')
        d += timedelta(days=7)
    # entregas
    for k, (d, nome) in enumerate(entregas):
        gx, ty = x(d), TOPO - (70, 50, 30)[k % 3]
        p.append(f'<line x1="{gx:.1f}" y1="{ty+4}" x2="{gx:.1f}" y2="{alt_total-BASE+4}" stroke="#b3372a" stroke-dasharray="4,3"/>')
        # rótulo perto da borda direita alinha pelo fim, senão é cortado
        anc = "end" if gx > LARG - 260 else "middle"
        p.append(f'<text x="{gx + (4 if anc == "middle" else 0):.1f}" y="{ty}" text-anchor="{anc}" font-size="12.5" fill="#b3372a">{esc(nome)} · {d:%d/%m}</text>')
    # barras
    y = TOPO
    for f, num, titulo, a, b, quem in linhas:
        bx, bw = x(a), max(x(b + timedelta(days=1)) - x(a), 4)
        p.append(f'<text x="168" y="{y+ALT/2+5:.0f}" font-size="13" fill="#1a1a1a">{esc(titulo[:40] + ("…" if len(titulo) > 40 else ""))}</text>')
        p.append(f'<rect x="{bx:.1f}" y="{y+(ALT-BARRA)/2:.1f}" width="{bw:.1f}" height="{BARRA}" rx="3" fill="{CORES[f]}"/>')
        p.append(f'<text x="{bx+bw+6:.1f}" y="{y+ALT/2+4:.0f}" font-size="12" fill="#444">{esc(quem)}</text>')
        y += ALT
    p.append(f'<text x="14" y="{alt_total-14}" font-size="12" fill="#555">Linhas vermelhas: entregas da disciplina. Barras: tarefas do quadro do GitHub, com o responsável ao lado.</text>')
    p.append("</svg>")
    open(destino, "w", encoding="utf-8").write("\n".join(p))


if __name__ == "__main__":
    svg(tarefas(), marcos(), sys.argv[1])
    print("ok", sys.argv[1])
