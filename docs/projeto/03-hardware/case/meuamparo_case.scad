// =====================================================================
//  MeuAmparo - case do dispositivo de deteccao de queda
//  Projeto aberto - licenca GNU GPL v3
//  Placa alvo: Waveshare ESP32-S3-SIM7670G-4G (110 x 30,44 mm)
//
//  COMO USAR
//  1. Meça a placa com paquímetro quando ela chegar e ajuste os
//     parâmetros marcados com "MEDIR". Só eles precisam mudar.
//  2. Renderize e exporte: openscad -o base.stl -D peca=1 este.scad
//                          openscad -o tampa.stl -D peca=2 este.scad
//  3. Envie os dois STL para o serviço de impressão.
// =====================================================================

peca = 0;          // 0 = conjunto aberto (visualizacao) | 1 = base | 2 = tampa
$fn = 48;

// ---------------------------------------------------------------------
// 1. PLACA  (valores do datasheet; os marcados MEDIR sao estimativa)
// ---------------------------------------------------------------------
pcb_comp        = 110.00;   // datasheet Waveshare
pcb_larg        =  30.44;   // datasheet Waveshare
pcb_esp         =   1.60;   // padrao
alt_sup_18650   =  19.50;   // MEDIR - altura do suporte da bateria sobre a placa
alt_inferior    =   3.00;   // MEDIR - altura dos componentes sob a placa

// Posicoes ao longo do comprimento, medidas da borda esquerda da placa
pos_usb         =   8.00;   // MEDIR - centro do conector USB-C
pos_leds_placa  =  22.00;   // MEDIR - centro do grupo de LEDs da placa
pos_antena_gnss =  92.00;   // MEDIR - centro da antena ceramica GNSS

// ---------------------------------------------------------------------
// 2. CAIXA
// ---------------------------------------------------------------------
folga    = 1.50;   // espaco livre entre placa e parede interna
parede   = 2.20;   // espessura da parede (3 perimetros a 0,4 mm + margem)
raio     = 3.00;   // arredondamento das quinas
lab_alt  = 2.50;   // altura do labio de encaixe entre base e tampa

int_comp = pcb_comp + 2*folga;
int_larg = pcb_larg + 2*folga;
int_alt  = alt_inferior + pcb_esp + alt_sup_18650 + folga;

ext_comp = int_comp + 2*parede;   // ~117,4 mm
ext_larg = int_larg + 2*parede;   // ~ 37,8 mm
ext_alt  = int_alt  + 2*parede;   // ~ 30,0 mm

alt_base = alt_inferior + pcb_esp + parede + 4;  // altura da bandeja inferior

// ---------------------------------------------------------------------
// 3. ABERTURAS
// ---------------------------------------------------------------------
usb_larg      =  9.50;   // recorte do USB-C
usb_alt       =  4.20;
bot_diam      = 12.00;   // botao de panico
bot_pos       = 30.00;   // centro do botao, a partir da esquerda
led_diam      =  5.20;   // LED RGB do projeto
led_pos       = 15.00;   // centro do LED, a partir da esquerda
jan_leds_c    = 22.00;   // janela sobre os LEDs da placa
jan_leds_l    =  7.00;
jan_leds_esp  =  0.80;   // parede fina: translucida quando impressa
buzzer_pos    = 62.00;   // centro da matriz de furos do buzzer
buzzer_furo   =  2.20;
ant_janela_c  = 26.00;   // parede fina sobre a antena GNSS
ant_janela_l  = 26.00;
ant_janela_esp=  1.20;   // MENOR parede possivel: o GNSS precisa "ver" o ceu
cordao_diam   =  4.50;   // ilhoses para o cordao

// =====================================================================
//  MODULOS
// =====================================================================

module caixa_ext(h) {
    hull() for (x=[raio, ext_comp-raio], y=[raio, ext_larg-raio])
        translate([x,y,0]) cylinder(h=h, r=raio);
}

module cavidade(h) {
    translate([parede, parede, parede])
        hull() for (x=[raio, int_comp-raio], y=[raio, int_larg-raio])
            translate([x,y,0]) cylinder(h=h, r=raio-0.5);
}

// pilares de fixacao nos 4 cantos - parafuso M2 auto-atarraxante
module pilares(h, furo) {
    for (x=[7, ext_comp-7], y=[6, ext_larg-6])
        translate([x,y,parede]) difference() {
            cylinder(h=h, d=6);
            translate([0,0,-0.1]) cylinder(h=h+0.2, d=furo);
        }
}

module furos_buzzer() {
    for (i=[-1:1], j=[-1:1])
        translate([buzzer_pos + i*4.5, ext_larg/2 + j*4.5, -1])
            cylinder(h=parede+2, d=buzzer_furo);
}

module ilhoses_cordao() {
    for (y=[ext_larg/2 - 7, ext_larg/2 + 7])
        translate([ext_comp-1, y, ext_alt/2]) rotate([0,90,0])
            cylinder(h=8, d=cordao_diam, center=true);
}

// ---------------------------------------------------------------------
//  BASE  - abriga a placa, o USB, o buzzer e o clipe de cinto
// ---------------------------------------------------------------------
module base() {
    difference() {
        union() {
            difference() {
                caixa_ext(alt_base);
                cavidade(alt_base);
                // recorte do USB-C na lateral esquerda
                translate([-1, ext_larg/2 - usb_larg/2, parede + alt_inferior - 1])
                    cube([parede+2, usb_larg, usb_alt+2]);
                furos_buzzer();
            }
            pilares(alt_base - parede, 1.6);
            // labio de encaixe
            translate([parede+0.4, parede+0.4, alt_base])
                difference() {
                    hull() for (x=[raio, int_comp-raio-0.8], y=[raio, int_larg-raio-0.8])
                        translate([x,y,0]) cylinder(h=lab_alt, r=raio-0.5);
                    translate([1.2,1.2,-0.1])
                        hull() for (x=[raio, int_comp-raio-3.2], y=[raio, int_larg-raio-3.2])
                            translate([x,y,0]) cylinder(h=lab_alt+0.2, r=raio-0.5);
                }
        }
        // rebaixo e furos M3 para o clipe de cinto, na face inferior
        translate([ext_comp/2 - 15, ext_larg/2 - 9, -0.1]) cube([30, 18, 1.2]);
        for (x=[ext_comp/2 - 9, ext_comp/2 + 9])
            translate([x, ext_larg/2, -1]) cylinder(h=parede+2, d=3.2);
    }
}

// ---------------------------------------------------------------------
//  TAMPA - leva o botao, o LED do projeto, a janela dos LEDs da placa
//          e a parede fina sobre a antena GNSS
// ---------------------------------------------------------------------
module tampa() {
    alt_t = ext_alt - alt_base;
    difference() {
        union() {
            difference() {
                caixa_ext(alt_t);
                translate([parede, parede, -0.1])
                    hull() for (x=[raio, int_comp-raio], y=[raio, int_larg-raio])
                        translate([x,y,0]) cylinder(h=alt_t-parede+0.1, r=raio-0.5);
            }
            // rebaixo interno da antena: deixa so 1,2 mm de plastico
            translate([pos_antena_gnss - ant_janela_c/2, ext_larg/2 - ant_janela_l/2, alt_t - parede])
                cube([ant_janela_c, ant_janela_l, 0.01]);
        }
        // botao de panico
        translate([bot_pos, ext_larg/2, -1]) cylinder(h=alt_t+2, d=bot_diam);
        // LED RGB do projeto
        translate([led_pos, ext_larg/2, -1]) cylinder(h=alt_t+2, d=led_diam);
        // janela translucida sobre os LEDs da placa
        translate([pos_leds_placa - jan_leds_c/2, ext_larg/2 - jan_leds_l/2, alt_t - parede])
            cube([jan_leds_c, jan_leds_l, parede - jan_leds_esp + 0.1]);
        // desbaste sobre a antena GNSS
        translate([pos_antena_gnss - ant_janela_c/2, ext_larg/2 - ant_janela_l/2, alt_t - parede])
            cube([ant_janela_c, ant_janela_l, parede - ant_janela_esp + 0.1]);
        // passagem dos parafusos
        for (x=[7, ext_comp-7], y=[6, ext_larg-6])
            translate([x,y,-1]) {
                cylinder(h=alt_t+2, d=2.4);
                translate([0,0,alt_t-1.4]) cylinder(h=2, d=4.6);   // rebaixo da cabeca
            }
        ilhoses_cordao();
    }
}

// =====================================================================
//  SAIDA
// =====================================================================
if (peca == 1) base();
else if (peca == 2) tampa();
else {
    base();
    translate([0, ext_larg + 12, 0]) tampa();
}

echo(str("EXTERNO: ", ext_comp, " x ", ext_larg, " x ", ext_alt, " mm"));
