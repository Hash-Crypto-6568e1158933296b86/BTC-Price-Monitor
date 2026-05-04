#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "secrets.h" // WiFi Configuration (WiFi name and Password)

// ---------- LOGO BITCOIN BITMAP ----------
const unsigned char bitcoinLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x03, 0xe7, 0xc0, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x03, 0xe7, 0xc0, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x02, 0x24, 0x40, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x02, 0x24, 0x40, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x02, 0x24, 0x40, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x02, 0x24, 0x40, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x02, 0x3c, 0x40, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0xfe, 0x3c, 0x7c, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x00, 0x00, 0x1f, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x00, 0x00, 0x01, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x03, 0xf0, 0x3f, 0x80, 0x60, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0xf0, 0x3f, 0xe0, 0x20, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x18, 0x30, 0x70, 0x30, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x18, 0x30, 0x10, 0x30, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x18, 0x30, 0x10, 0x30, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x18, 0x30, 0x10, 0x30, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x18, 0x30, 0x30, 0x20, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x18, 0x30, 0xe0, 0x60, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x3f, 0xc0, 0xc0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x00, 0x01, 0xc0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x00, 0x00, 0xf0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x00, 0x00, 0x38, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x3f, 0xe0, 0x18, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x30, 0xf8, 0x0c, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x18, 0x30, 0x1c, 0x0c, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x18, 0x30, 0x0c, 0x0c, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x18, 0x30, 0x04, 0x0c, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x18, 0x30, 0x0c, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x18, 0x30, 0x0c, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x18, 0x30, 0x38, 0x0c, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0xf0, 0x3f, 0xf0, 0x08, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x01, 0xe0, 0x1f, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x01, 0x00, 0x00, 0x00, 0x30, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x00, 0x00, 0x0f, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0xfe, 0x3c, 0x7e, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x02, 0x3c, 0x40, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x02, 0x24, 0x40, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x02, 0x24, 0x40, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x02, 0x24, 0x40, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x02, 0x24, 0x40, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x03, 0xe7, 0xc0, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x03, 0xe7, 0xc0, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// ---------- PROTÓTIPOS ----------
void showSplashScreen();
void drawLayout();
void updatePrice(double price, double change, String high, String low);
void drawStatusBar();
void drawGraphBackground();
void updateGraph(double price);
void drawAmbientBackground();
void drawBootLogo(int x, int y, int visibleColumns, uint16_t bodyColor, uint16_t glowColor);
uint16_t blend565(uint16_t from, uint16_t to, uint8_t amount);

// ---------- OBJETOS ----------
TFT_eSPI tft = TFT_eSPI();
WiFiClientSecure client;
HTTPClient http;

// ---------- WIFI ----------
const char* ssid = "SSID";
const char* password = "WIFI_PASSWORD";

// ---------- API ----------
const char* url = "https://api.binance.com/api/v3/ticker/24hr?symbol=BTCUSDT";

// ============================================================
//  PALETA DE CORES — METRO / WINDOWS PHONE FLAT DESIGN
//
//  Princípios:
//    • Sem gradientes em cards — cores sólidas planas
//    • Tiles com borda lateral accent (estilo Metro)
//    • Tipografia bold, sem sombras
//    • Grid sutil no gráfico, linha limpa
// ============================================================

// ── Fundos ────────────────────────────────────────────────
// METRO_BG       = RGB(  6,  8, 18) → preto-navy
// METRO_SURFACE  = RGB(  8, 22, 55) → navy visível nos cards
// METRO_HEADER_BG= RGB(  0, 80,160) → azul Windows Phone nítido
// METRO_GRAPH_BG = RGB(  4,  8, 20) → fundo do gráfico quase-preto
#define METRO_BG          0x0042    // RGB(  6,  8, 18)  ← preto-navy
#define METRO_SURFACE     0x0977    // RGB(  8, 44, 55)  — checado: R=1→8 G=11→44 B=23→184... ajuste via tft.color565 abaixo
#define METRO_GRAPH_BG    0x0042    // igual ao BG
#define METRO_HEADER_BG   0x0294    // RGB(  0, 80,160)  — azul Metro correto

// ── Accent Metro (azul cobalto Windows Phone) ─────────────
// 0x035F = RGB(0, 104, 248) — azul vivo ✓
#define METRO_ACCENT      0x035F    // RGB(  0,104,248)  — azul Metro vivo

// ── Texto ─────────────────────────────────────────────────
// COLOR_SUBTEXT  = RGB( 96,140,196) — cinza-azulado Metro
// COLOR_DIM      = RGB( 64, 96,140) — texto secundário
#define COLOR_TEXT        0xFFFF    // Branco puro
#define COLOR_SUBTEXT     0x6477    // RGB( 96,140,184)  — label azulado
#define COLOR_DIM         0x42B1    // RGB( 64, 88,136)  — texto apagado

// ── Destaques ─────────────────────────────────────────────
#define COLOR_GOLD        0xFE20    // Dourado (logo BTC)
#define COLOR_RED_TILE    0xF800    // Vermelho puro

// ── Grid e separadores ────────────────────────────────────
#define METRO_GRID        0x10E3    // RGB( 16, 28, 48)  — grade sutil
#define METRO_SEPARATOR   0x2145    // RGB( 32, 40, 80)  — separador

// ── CORES PARA VARIAÇÃO ───────────────────────────────────────
// Com tft.invertDisplay(true) no setup, cores sao normais:
//   vermelho real = 0xF800, azul = METRO_ACCENT
#define COLOR_VERMELHO_DISPLAY  0xF800   // Vermelho real (bearish)
#define COLOR_PRETO_DISPLAY     0x0000   // Preto real

// Compatibilidade
#define COLOR_BG          METRO_BG
#define COLOR_DARK_BG     METRO_SURFACE
#define COLOR_CYAN        METRO_ACCENT
#define COLOR_DARK_GRAY   0x2945
#define COLOR_LIGHT_GRAY  0xCE79
#define COLOR_MED_GRAY    0x7BEF
#define COLOR_BLACK       0x0000

// ---------- CONFIGURAÇÕES DE DISPLAY ----------
#define SCREEN_WIDTH   320
#define SCREEN_HEIGHT  240

// ---------- CONFIGURAÇÕES DO GRÁFICO ----------
// Layout do display (total = 240px):
//   Header    :   0 – 32  (32px)
//   Card      :  34 – 175 (142px)
//   Gap       : 176 – 177 (2px)
//   Gráfico   : 178 – 229 (52px)
//   Status bar: 230 – 239 (10px)
#define GRAPH_X       0
#define GRAPH_Y       178
#define GRAPH_WIDTH   320
#define GRAPH_HEIGHT  52
#define MAX_DATA_POINTS 160

// ---------- VARIÁVEIS GLOBAIS ----------
unsigned long lastUpdate = 0;
bool firstRun = true;
double priceHistory[MAX_DATA_POINTS];
int dataCount = 0;
double minPrice = 999999;
double maxPrice = 0;
double previousPrice = 0;

// ============================================================
//  SETUP
// ============================================================
void setup() {
  Serial.begin(115200);
  randomSeed(micros());

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.init();
  tft.setRotation(3);
  // O driver TFT_eSPI inicializa este painel com INVON (inversao ligada).
  // invertDisplay(false) envia o comando INVOFF para desligar a inversao,
  // fazendo as cores aparecerem corretamente (azul=azul, preto=preto).
  tft.invertDisplay(false);
  tft.fillScreen(METRO_BG);

  showSplashScreen();
  delay(2500);

  // ── Tela de conexão WiFi — Metro style ──────────────────
  drawAmbientBackground();

  // Container do card de conexão — tile Metro flat
  uint16_t cardBg = tft.color565(8, 22, 55);   // navy visível
  tft.fillRect(36, 76, 248, 90, cardBg);
  // Borda lateral accent (marcador Metro)
  tft.fillRect(36, 76, 5, 90, METRO_ACCENT);
  // Borda superior accent fina
  tft.drawFastHLine(36, 76, 248, METRO_ACCENT);

  // Título
  tft.setTextSize(2);
  tft.setTextColor(COLOR_TEXT, cardBg);
  tft.setCursor(56, 92);
  tft.print("Conectando WiFi");

  // Subtítulo
  tft.setTextSize(1);
  tft.setTextColor(COLOR_SUBTEXT, cardBg);
  tft.setCursor(72, 114);
  tft.print("Sincronizando mercado...");

  // Barra de progresso — fundo
  tft.fillRect(68, 136, 188, 8, METRO_GRID);

  WiFi.begin(SSID, WIFI_PASSWORD);
  int connectFrame = 0;
  while (WiFi.status() != WL_CONNECTED) {
    // Barra de progresso animada — Metro (sem gradiente, só fill sólido)
    int fillWidth = 12 + ((connectFrame % 10) * 17);
    if (fillWidth > 184) fillWidth = 184;
    tft.fillRect(68, 136, 188, 8, METRO_GRID);
    tft.fillRect(68, 136, fillWidth, 8, METRO_ACCENT);

    // Indicador de progresso textual
    tft.setTextSize(1);
    tft.setTextColor(COLOR_DIM, cardBg);
    tft.setCursor(86, 152);
    const char* dots = (connectFrame % 3 == 0) ? "aguarde.  " : (connectFrame % 3 == 1) ? "aguarde.. " : "aguarde...";
    tft.print(dots);

    delay(500);
    Serial.print(".");
    connectFrame++;
  }

  Serial.println("\nWiFi conectado!");
  client.setInsecure();

  for (int i = 0; i < MAX_DATA_POINTS; i++) {
    priceHistory[i] = 0;
  }

  drawLayout();
  drawGraphBackground();
  drawStatusBar();
}

// ============================================================
//  LOOP
// ============================================================
void loop() {
  http.begin(client, url);
  http.setTimeout(10000);

  int httpCode = http.GET();

  if (httpCode != 200) {
    Serial.printf("Erro HTTP: %d\n", httpCode);
    http.end();
    delay(5000);
    return;
  }

  String payload = http.getString();
  http.end();

  #if ARDUINOJSON_VERSION_MAJOR >= 7
  JsonDocument doc;
  #else
  DynamicJsonDocument doc(4096);
  #endif

  DeserializationError jsonError = deserializeJson(doc, payload);
  if (jsonError) {
    Serial.printf("Erro JSON: %s\n", jsonError.c_str());
    delay(5000);
    return;
  }

  double currentPrice  = doc["lastPrice"].as<double>();
  double priceChange   = doc["priceChange"].as<double>();
  String high24h       = doc["highPrice"];
  String low24h        = doc["lowPrice"];

  if (firstRun) {
    previousPrice = currentPrice;
    firstRun = false;
  }

  updatePrice(currentPrice, priceChange, high24h, low24h);
  updateGraph(currentPrice);
  drawStatusBar();

  previousPrice = currentPrice;
  lastUpdate = millis();

  delay(2000);
}

// ============================================================
//  SPLASH SCREEN — Metro Flat
//  Logo BTC + tile de título + barra de progresso plana
// ============================================================
void showSplashScreen() {
  tft.fillScreen(METRO_BG);

  // Logo BTC com reveal animation (mantida da versão original)
  int logoX = 160 - 64;
  int logoY = 26;

  for (int frame = 0; frame <= 24; frame++) {
    int revealColumns = frame * 6;
    drawBootLogo(logoX, logoY, revealColumns, COLOR_TEXT, COLOR_GOLD);
    delay(20);
  }

  // Linha accent Metro sob o logo
  tft.fillRect(70, 96, 180, 3, METRO_ACCENT);

  // Tile de título — Metro flat (cor viva, sem gradiente)
  uint16_t tileBg = tft.color565(0, 80, 160);  // azul Metro nítido
  tft.fillRect(58, 104, 204, 64, tileBg);
  // Marcador lateral accent (o "tile edge" característico do Metro)
  tft.fillRect(58, 104, 5, 64, METRO_ACCENT);

  tft.setTextColor(COLOR_GOLD, tileBg);
  tft.setTextSize(3);
  tft.setCursor(76, 114);
  tft.print("BITCOIN");

  tft.setTextColor(COLOR_TEXT, tileBg);
  tft.setTextSize(2);
  tft.setCursor(80, 146);
  tft.print("PRICE");

  // Barra de progresso flat — fundo + fill animado
  tft.fillRect(78, 190, 164, 8, METRO_GRID);
  for (int i = 0; i <= 160; i += 5) {
    tft.fillRect(78, 190, i, 8, METRO_ACCENT);
    delay(11);
  }

  // Créditos
  tft.setTextSize(1);
  tft.setTextColor(COLOR_DIM, METRO_BG);
  tft.setCursor(96, 210);
  tft.print("Developed by HashCode");
}

// ============================================================
//  LAYOUT — Header Metro plano
// ============================================================
void drawLayout() {
  drawAmbientBackground();

  // ── Header bar flat ──────────────────────────────────────
  tft.fillRect(0, 0, SCREEN_WIDTH, 32, METRO_HEADER_BG);

  // Badge circular BTC (dourado)
  tft.fillCircle(18, 16, 11, COLOR_GOLD);
  tft.setTextSize(2);
  tft.setTextColor(METRO_BG, COLOR_GOLD);
  tft.setCursor(14, 9);
  tft.print("B");

  // Título BITCOIN
  tft.setTextSize(2);
  tft.setTextColor(COLOR_TEXT, METRO_HEADER_BG);
  tft.setCursor(34, 9);
  tft.print("BITCOIN");

  // Badge LIVE — tile vermelho plano (sem borda arredondada)
  tft.fillRect(148, 8, 36, 16, COLOR_RED_TILE);
  tft.setTextSize(1);
  tft.setTextColor(COLOR_TEXT, COLOR_RED_TILE);
  tft.setCursor(156, 12);
  tft.print("LIVE");

  // Par BTC/USDT
  tft.setTextColor(COLOR_SUBTEXT, METRO_HEADER_BG);
  tft.setTextSize(1);
  tft.setCursor(200, 12);
  tft.print("BTC/USDT");

  // Linha separadora accent (o "underline" Metro)
  tft.drawFastHLine(0, 32, SCREEN_WIDTH, METRO_ACCENT);
  tft.drawFastHLine(0, 33, SCREEN_WIDTH, METRO_SURFACE);
}

// ============================================================
//  PRICE UPDATE — Metro Tile Card
//  Flat, sem gradientes, com marcador lateral accent
// ============================================================
void updatePrice(double price, double change, String high, String low) {
  double realTimeChange  = price - previousPrice;
  double changePercent   = (realTimeChange / previousPrice) * 100;
  bool   isUp            = realTimeChange >= 0;

  // Cor de tendência — respeita a inversão do display
  // METRO_ACCENT aparece como azul; COLOR_VERMELHO_DISPLAY aparece como vermelho
  uint16_t trendColor = isUp ? METRO_ACCENT : COLOR_VERMELHO_DISPLAY;

  // ── Card principal — tile Metro flat ──────────────────────
  uint16_t cardBg = tft.color565(8, 22, 55);   // navy visível (não quase-preto)
  tft.fillRect(0, 34, SCREEN_WIDTH, 142, cardBg);

  // Marcador lateral esquerdo (o "tile edge" Metro — muda com tendência)
  //tft.fillRect(0, 34, 6, 142, trendColor);

  // ── Badge de tendência — tile flat no topo ────────────────
  uint16_t badgeBg = trendColor;
  tft.fillRect(12, 42, 78, 14, badgeBg);
  tft.setTextSize(1);
  tft.setTextColor(COLOR_TEXT, badgeBg);
  tft.setCursor(20, 46);
  tft.print(isUp ? "\x18 UPTICK" : "\x19 DOWNTICK");  // ↑ / ↓

  // Percentual de variação — alinhado à direita
  tft.setTextSize(1);
  tft.setTextColor(trendColor, cardBg);
  tft.setCursor(232, 46);
  tft.printf("%+.2f%%", changePercent);

  // ── PREÇO PRINCIPAL — grande, centralizado ────────────────
  char priceStr[20];
  sprintf(priceStr, "$%.2f", price);
  int priceWidth = strlen(priceStr) * 24;  // 24px por char em size 4
  int priceX     = (SCREEN_WIDTH - priceWidth) / 2;

  tft.setTextSize(4);
  tft.setTextColor(COLOR_TEXT, cardBg);
  tft.setCursor(priceX, 60);
  tft.print(priceStr);

  // ── Variação 24H — linha menor sob o preço ────────────────
  char changeStr[30];
  sprintf(changeStr, "%s$%.2f (%.2f%%)",
          change >= 0 ? "+" : "",
          change,
          (change / (price - change)) * 100);
  int changeWidth = strlen(changeStr) * 12;  // 12px por char em size 2
  int changeX     = (SCREEN_WIDTH - changeWidth) / 2;

  uint16_t changeColor = (change >= 0) ? METRO_ACCENT : COLOR_VERMELHO_DISPLAY;
  tft.setTextSize(2);
  tft.setTextColor(changeColor, cardBg);
  tft.setCursor(changeX, 100);
  tft.print(changeStr);

  // ── Separador horizontal sutil ────────────────────────────
  tft.drawFastHLine(12, 120, SCREEN_WIDTH - 24, METRO_GRID);

  // ── TILE HIGH 24H — azul visível, marcador accent ─────────
  uint16_t highBg = tft.color565(0, 55, 115);  // azul escuro visível
  tft.fillRect(10, 126, 142, 44, highBg);
  tft.fillRect(10, 126, 5, 44, METRO_ACCENT);

  tft.setTextSize(1);
  tft.setTextColor(COLOR_TEXT, highBg);   // branco sobre azul
  tft.setCursor(22, 132);
  tft.print("HIGH 24H");

  tft.setTextSize(2);
  tft.setTextColor(0x5FFF, highBg);  // azul ciano claro sobre azul escuro
  tft.setCursor(22, 144);
  tft.print("$");
  tft.print((int)high.toDouble());

  // ── TILE LOW 24H — vermelho visível, marcador vermelho ────
  uint16_t lowBg = tft.color565(80, 12, 18);   // vermelho escuro visível
  tft.fillRect(168, 126, 142, 44, lowBg);
  tft.fillRect(168, 126, 5, 44, COLOR_VERMELHO_DISPLAY);

  tft.setTextSize(1);
  tft.setTextColor(COLOR_TEXT, lowBg);   // branco sobre vermelho
  tft.setCursor(180, 132);
  tft.print("LOW 24H");

  tft.setTextSize(2);
  tft.setTextColor(0xFB8C, lowBg);   // vermelho claro (salmão) sobre vermelho escuro
  tft.setCursor(180, 144);
  tft.print("$");
  tft.print((int)low.toDouble());
}

// ============================================================
//  GRAPH BACKGROUND — Metro Minimal
//  Fundo plano + grid horizontal sutil + linha accent no topo
// ============================================================
void drawGraphBackground() {
  // Fundo plano
  tft.fillRect(GRAPH_X, GRAPH_Y, GRAPH_WIDTH, GRAPH_HEIGHT, METRO_GRAPH_BG);

  // Linha accent no topo do gráfico (Metro tile top border)
  tft.drawFastHLine(GRAPH_X, GRAPH_Y, GRAPH_WIDTH, METRO_ACCENT);

  // Linhas de grade horizontais — muito sutis
  for (int i = 1; i <= 3; i++) {
    int y = GRAPH_Y + (GRAPH_HEIGHT * i / 4);
    tft.drawFastHLine(GRAPH_X, y, GRAPH_WIDTH, METRO_GRID);
  }
}

// ============================================================
//  GRAPH UPDATE — Metro Clean Line
//  Área fill sólida + linha de preço limpa + marcadores flat
// ============================================================
void updateGraph(double price) {
  // Shift left (mantido do original)
  for (int i = 0; i < MAX_DATA_POINTS - 1; i++) {
    priceHistory[i] = priceHistory[i + 1];
  }
  priceHistory[MAX_DATA_POINTS - 1] = price;
  if (dataCount < MAX_DATA_POINTS) dataCount++;

  if (price < minPrice) minPrice = price;
  if (price > maxPrice) maxPrice = price;

  drawGraphBackground();
  if (dataCount < 2) return;

  // Escala dinâmica (mantida do original)
  double currentMin = price, currentMax = price;
  int startIndex = MAX_DATA_POINTS - dataCount;

  for (int i = startIndex; i < MAX_DATA_POINTS; i++) {
    if (priceHistory[i] > 0) {
      if (priceHistory[i] < currentMin) currentMin = priceHistory[i];
      if (priceHistory[i] > currentMax) currentMax = priceHistory[i];
    }
  }

  double range = currentMax - currentMin;
  if (range == 0) range = price * 0.01;
  currentMin -= range * 0.1;
  currentMax += range * 0.1;

  // Cor do gráfico baseada na tendência
  bool trendingUp  = (dataCount > 1 && price >= priceHistory[MAX_DATA_POINTS - 2]);
  uint16_t graphColor = trendingUp ? METRO_ACCENT : COLOR_VERMELHO_DISPLAY;

  // Fill da área — azul muito escuro (up) ou vermelho muito escuro (down)
  uint16_t fillColor = trendingUp
    ? tft.color565(0, 35, 90)    // azul navy visível
    : tft.color565(60, 8, 12);   // vermelho escuro visível

  int lastX = -1, lastY = -1;
  int pixelsPerPoint = 2;

  // ── Desenha área fill + linha ──────────────────────────────
  for (int i = startIndex; i < MAX_DATA_POINTS; i++) {
    if (priceHistory[i] == 0) continue;

    int pointIndex = i - startIndex;
    int x = GRAPH_X + (pointIndex * pixelsPerPoint);
    if (x >= GRAPH_X + GRAPH_WIDTH) break;

    double normalizedPrice = (priceHistory[i] - currentMin) / (currentMax - currentMin);
    int y = GRAPH_Y + GRAPH_HEIGHT - (normalizedPrice * (GRAPH_HEIGHT - 3));
    y = constrain(y, GRAPH_Y + 1, GRAPH_Y + GRAPH_HEIGHT - 1);

    // Área fill (coluna sólida até o fundo)
    tft.drawFastVLine(x, y, (GRAPH_Y + GRAPH_HEIGHT) - y, fillColor);

    // Linha principal sobre a área fill
    if (lastX != -1) {
      tft.drawLine(lastX, lastY, x, y, graphColor);
    }

    lastX = x;
    lastY = y;
  }

  // ── Marcador do preço atual ────────────────────────────────
  if (lastX != -1 && lastY != -1) {
    // Linha horizontal pontilhada no nível do preço atual
    for (int px = GRAPH_X + 60; px < GRAPH_WIDTH - 4; px += 6) {
      tft.drawPixel(px, lastY, blend565(METRO_GRAPH_BG, graphColor, 90));
      tft.drawPixel(px + 1, lastY, blend565(METRO_GRAPH_BG, graphColor, 90));
    }

    // Ponto sólido no preço atual (sem efeito pulsante — Metro é flat)
    tft.fillCircle(lastX, lastY, 3, graphColor);
    // Anel externo fino
    tft.drawCircle(lastX, lastY, 5, blend565(METRO_GRAPH_BG, graphColor, 140));

    // Label do preço atual — tile flat (sem borda arredondada)
    char priceLabel[12];
    sprintf(priceLabel, "$%.0f", price);
    int labelY = constrain(lastY - 8, GRAPH_Y + 2, GRAPH_Y + GRAPH_HEIGHT - 10);
    tft.fillRect(GRAPH_X + 4, labelY - 1, 56, 12, graphColor);
    tft.setTextSize(1);
    tft.setTextColor(COLOR_TEXT, graphColor);
    tft.setCursor(GRAPH_X + 8, labelY + 2);
    tft.print(priceLabel);

    // Badge LIVE — tile flat à direita
    tft.fillRect(GRAPH_X + GRAPH_WIDTH - 30, GRAPH_Y + 3, 28, 12, METRO_ACCENT);
    tft.setTextColor(COLOR_TEXT, METRO_ACCENT);
    tft.setCursor(GRAPH_X + GRAPH_WIDTH - 26, GRAPH_Y + 6);
    tft.print("LIVE");
  }
}

// ============================================================
//  AMBIENT BACKGROUND — Metro Flat
//  Fundo sólido plano. Sem partículas, sem círculos, sem gradiente.
// ============================================================
void drawAmbientBackground() {
  tft.fillScreen(METRO_BG);

  // Linhas de grid sutis com tint azul (Metro tile feel)
  for (int y = 38; y < SCREEN_HEIGHT - 12; y += 40) {
    tft.drawFastHLine(0, y, SCREEN_WIDTH, METRO_GRID);
  }

  // Linha accent vertical esquerda — marca lateral do "tile" Metro
  tft.drawFastVLine(0, 34, 142, METRO_ACCENT);
}

// ============================================================
//  STATUS BAR — Metro Minimal
//  Barra flat no rodapé: uptime | última atualização | WiFi
// ============================================================
void drawStatusBar() {
  int barY = SCREEN_HEIGHT - 10;
  tft.fillRect(0, barY, SCREEN_WIDTH, 10, METRO_HEADER_BG);

  tft.setTextSize(1);

  // Uptime
  tft.setTextColor(COLOR_DIM, METRO_HEADER_BG);
  unsigned long hours   = millis() / 3600000;
  unsigned long minutes = (millis() / 60000) % 60;
  unsigned long seconds = (millis() / 1000) % 60;
  tft.setCursor(4, barY + 2);
  tft.printf("Up:%02lu:%02lu:%02lu", hours, minutes, seconds);

  // Última atualização
  unsigned long secondsSinceUpdate = (millis() - lastUpdate) / 1000;
  tft.setTextColor(COLOR_SUBTEXT, METRO_HEADER_BG);
  tft.setCursor(110, barY + 2);
  if (secondsSinceUpdate < 60) {
    tft.print("Atualizado agora");
  } else if (secondsSinceUpdate < 3600) {
    tft.printf("Atual.%lum atras", secondsSinceUpdate / 60);
  } else {
    tft.printf("Atual.%luh atras", secondsSinceUpdate / 3600);
  }

  // Status WiFi — tile flat à direita
  if (WiFi.status() == WL_CONNECTED) {
    tft.fillRect(SCREEN_WIDTH - 44, barY, 44, 10, METRO_ACCENT);
    tft.setTextColor(COLOR_TEXT, METRO_ACCENT);
    tft.setCursor(SCREEN_WIDTH - 40, barY + 2);
    tft.print("WiFi ON");
  } else {
    tft.fillRect(SCREEN_WIDTH - 48, barY, 48, 10, COLOR_VERMELHO_DISPLAY);
    tft.setTextColor(COLOR_TEXT, COLOR_VERMELHO_DISPLAY);
    tft.setCursor(SCREEN_WIDTH - 44, barY + 2);
    tft.print("WiFi OFF");
  }
}

// ============================================================
//  FUNÇÕES AUXILIARES — mantidas do original
// ============================================================

void drawBootLogo(int x, int y, int visibleColumns, uint16_t bodyColor, uint16_t glowColor) {
  int revealLimit = constrain(visibleColumns, 0, 128);
  for (int py = 0; py < 64; py++) {
    for (int px = 0; px < revealLimit; px++) {
      int byteIndex = (py * 16) + (px / 8);
      int bitIndex  = 7 - (px % 8);
      if (pgm_read_byte(&bitcoinLogo[byteIndex]) & (1 << bitIndex)) {
        if (px > 0 && py > 0) {
          tft.drawPixel(x + px - 1, y + py - 1, glowColor);
        }
        tft.drawPixel(x + px, y + py, bodyColor);
      }
    }
  }
}

uint16_t blend565(uint16_t from, uint16_t to, uint8_t amount) {
  uint8_t inv = 255 - amount;

  uint8_t r1 = (from >> 11) & 0x1F;
  uint8_t g1 = (from >> 5)  & 0x3F;
  uint8_t b1 =  from        & 0x1F;

  uint8_t r2 = (to >> 11) & 0x1F;
  uint8_t g2 = (to >> 5)  & 0x3F;
  uint8_t b2 =  to        & 0x1F;

  uint8_t r = ((r1 * inv) + (r2 * amount)) / 255;
  uint8_t g = ((g1 * inv) + (g2 * amount)) / 255;
  uint8_t b = ((b1 * inv) + (b2 * amount)) / 255;

  return (r << 11) | (g << 5) | b;
}

// drawRoundedRect mantida para compatibilidade (não usada no Metro)
void drawRoundedRect(int x, int y, int w, int h, int r, uint16_t color, uint16_t borderColor = 0xFFFF) {
  tft.fillRoundRect(x, y, w, h, r, color);
  tft.drawRoundRect(x, y, w, h, r, borderColor);
}
