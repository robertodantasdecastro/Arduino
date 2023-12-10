#define PinFech 9 //8
#define PinAbre 10 //12
#define PinSensrFech 4
#define PinSensrAbre 7
#define PinLedVerm A2
#define pinLedVerd A3
#define pinLedAzul A4 //  5 - >PWM
#define pinAnpereMotor A5
#define rxPin 2
#define txPin 3
#define PinIR 6  /// 6 -> PWM
#define progBTN 11
#define voltPIN 13
#define cargaRELE A1


long tempo = 0;

SoftwareSerial rfid = SoftwareSerial( rxPin, txPin );
int permitido = 0;

int TempoAberto = 20;


IRrecv irrecv(PinIR);
decode_results resultadoIR;

int EstadoSensAbre;
int EstadoSensFech;
int Atividade = 0;
int inicio=0;
int parado = 1;

int VelInicio = 220;
int VelMax = 300;
int VelAtual = 0;
int VelMin = 0; // tem que ser 0 -- 
int EstadoAtual = 0;


int p = 0;


int autoTeste = 0;

int NumeroDeChaves = sizeof(ChavesPermitidas)/sizeof(ChavesPermitidas[0]);

int ByteInicio = 0; 
int cont=0;
int cheio=0;
