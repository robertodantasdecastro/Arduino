#define rxPin 2
#define txPin 3  //    ---> PWM
#define cargaRELE 4
#define PinFech 5 //   ---> PWM
#define PinAbre 6 //   ---> PWM
#define PinIR 7
#define progBTN 8
#define PinSensrFech 12  //A3
#define PinSensrAbre 13  //A4
#define pinAmpereMotor A2 
#define voltPIN A1
#define PinLedVerm  0 //11   //-->PWM
#define pinLedVerd  10 //10   //-->PWM
#define pinLedAzul  9  //9    //-->PWM

long tempo = 0;


long TT = 0;
int TempVerBat = 10;   // Tempo p/ verificar volt da bateria
float VoltMin = 11.90;
float VoltMax = 12.50;
int EstadoCarga = 0;
float Vvolt = 0.00;
float Avalor = 0.00;

SoftwareSerial rfid = SoftwareSerial( rxPin, txPin );
int permitido = 0;

int TempoAberto = 20;


int EstadoSensAbre;
int EstadoSensFech;
int Atividade = 0;
int inicio=0;
int parado = 1;

int velDelay =30;
int velFadePorta = 5;
int VelInicio = 100;
int VelMax = 255;
int VelMenor = 90;
int VelAtual = 0;
int VelMin = 0; // tem que ser 0 -- 
int EstadoAtual = 0;


int p = 0;


int autoTeste = 0;

int NumeroDeChaves = sizeof(ChavesPermitidas)/sizeof(ChavesPermitidas[0]);

int ByteInicio = 0; 
int cont=0;
int cheio=0;

