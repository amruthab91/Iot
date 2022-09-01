int value2[]= {61,62,59,58,60,62,64,68,69,70,70,65,65,65,66,65,61,66,63,66,64,64,65,61,63,65,63,63,64,61,62,68,67,69,68,78,78,74,68,66,63,65,62,58,57,57,61,61,62,22,1,60,189,300,309,289,140,40,50,51,46,44,46,49,48,49,53,55,53,54,57,59,61,60,62,65,63,65,63,62,60,61,61,61,61,66,70,68,66,69,66,62,67,65,64,65,66,67,64,64,64,63,65,66,64,64,61,62,66,68,71,71,72,81,76,74,71,66,64,64,61,58,56,61,61,62,54,0,20,132,278,331,313,183,60,52,52,51,51,47,49,51,52,52,54,54,56,59,58,61,65,64,67,66,66,68,62,61,60,60,61,59,64,67,67,68,68,66,67,66,66,65,66,66,66,66,67,67,68,65,66,67,68,67,67,67,69,72,73,74,81,77,71,68,72,68,63,62,62,60};
int value[]= {108,107,107,107,107,107,107,107,107,105,107,106,107,105,106,107,105,100,107,103,104,104,105,109,118,120,129,142,137,121,114,112,110,88,87,87,89,83,105,181,283,317,99,0,28,66,93,93,94,93,99,95,100,102,108,108,110,110,115,119,122,128,133,137,143,141,146,148,145,146,145,141,140,133,131,121,119,120,116,115,115,115,114,119,113,116,116,113,112,110,114,109,111,110,108,104,107,111,107,107,106,104,107,108,107,108,106,102,108,106,103,107,107,105,105,102,107,103,107,103,102,105,104,102,106,106,117,126,119,138,143,131,127,109,114,90,89,88,93,89,95,153,261,313,153,50,9,34,83,92,96,93,98,102,98,102,105,111,113,111,113,119,121,124,131,129,140,136,140,140,147,141,142,139,136,135,126,125,119,117,116,115,114,119,113,113,114,112,112,108,108,109,104,104,108,107,106,107,103,104};
float EMA_ALPHA = 0.2;
int EMA_HP = 0;
int EMA_LP = 0;
int aux[300];
int m=0;
int m2=0;
int med=0;
int med2=0;
int mod=0;
int mod2=0;
int des=0;
int des2=0;
int vrms1=0;
int vrms2=0;
int maximo1=0;
int maximo2=0;
int maximo3=0;
int d1=0;
int d2=0;
int value2Length = sizeof(value2)/sizeof(int) ;
int value2Length_sin = sizeof(value2);
int valueLength = sizeof(value) / sizeof(int);
int valueLength_sin = sizeof(value);

int getMeasure()
{
   int static index = 0;
   index++;
   return value[index - 1];
}

int getMeasure2(){
   int static index = 0;
   index++;
   return value2[index - 1];
}

int EMAHighPassFilter(int value){
   EMA_LP = EMA_ALPHA * value + (1 - EMA_ALPHA) * EMA_LP;
   EMA_HP = value - EMA_LP;
 
   return EMA_HP;
}

int media(int longitud, int *vector){
  int num=0;
  for(int cont=0; cont<longitud; cont++){
    num=vector[cont]+num;
  }
  int media1=0;
  media1=num/longitud;
  
  return media1;
}

int mediana(int longitud, int *vector){
  int mediana1;
  int bandera=0;
  
  for(int cont=0;cont<longitud;cont++) {
    aux[cont]=vector[cont];
   }

  for(int cont=longitud-1;cont<longitud;cont--) {
    if(cont>0 && bandera==0){
      bandera=1;
      for(int conta=0;conta<cont;conta++) {
        if(aux[conta]>aux[conta+1]) {
          int numero = aux[conta];
          aux[conta] = aux[conta+1];
          aux[conta+1]=numero;
          bandera=0;
        }
      }
    }
  }
   
  maximo1=aux[199];
  maximo2=aux[198];
  maximo3=aux[197];
  
  if(longitud%2!=0) {
    mediana1=aux[longitud/2];
  }else{
    mediana1=((aux[longitud/2]+aux[(longitud/2)-1])/2);
  } 
  
  return maximo1,maximo2,maximo3, mediana1;
}

int moda(int longitud, int *vector){
  int moda1=0;
  for(int cont=0;cont<longitud;cont++) {
        aux[cont]=0;
   }
  
  for(int cont=0;cont<longitud;cont++) {
        int numero= vector[cont];
        int posicion = cont;
        for(int conta=cont;conta<longitud;conta++) {
          if(vector[conta]==numero){
               aux[posicion]++;
          }
        }
    }
    int mayor=aux[0];
    int posmayor = 0;
    for(int cont=0;cont<longitud;cont++) {
        if(aux[cont]>mayor) {
            posmayor=cont;
            mayor=aux[cont];
        }
    }
   moda1= vector[posmayor]; 
  return moda1;
}

long desviacion(int longitud, int *vector){
  long num2=0,num=0;
  int media2=0;
  int desv=0;
  
  for(int cont=0; cont<longitud; cont++){
    num=vector[cont]+num;
  }
  
  media2=num/longitud;

  for(int cont=0; cont<longitud; cont++){
      int m= (vector[cont]-media2);
      long p=pow(m,2);
      num2=p+num2;
  }
  
  int media3=0;
  media3=num2/longitud;
  desv=sqrt(media3);
  
  return desv;
}

float vrms(int longitud, int *vector){
  float sum=0;
  float x=0;
  int v=0;
  for(int i=0; i<longitud; i++){
    sum=pow(vector[i],2)+sum;
  }
 
  x=sum/longitud;
  v=sqrt(x);
  
  return v;
}

int distance(int longitud, int *vector, int max, int max2){
  int disn=0;
  int cab=0;
  int col=0;
  
  for(int i=0; i<longitud; i++){
    if(vector[i] == max){
      cab=i;
   	}
   	if(vector[i] == max2){
      col=i;
   	}
  }
  
  if(cab>col){
    disn = cab-col;
  }else{
    disn = col-cab;
  }
  return disn;
}



void setup()
{
  Serial.begin(115200);   
  DDRD = 0b11111100;
  Serial.print(value2Length);
  Serial.print(value2Length_sin);
  Serial.print(valueLength);
  Serial.print(valueLength_sin);
  
  for (int cont = 0; cont < value2Length; cont++){
    int value = getMeasure();
    int value2 = getMeasure2();
    int filtered = EMAHighPassFilter(value);
    int filtered2 = EMAHighPassFilter(value2);
    Serial.print(filtered);
   	Serial.print(",");
    Serial.print(filtered2);
    Serial.println();
   }
  
  m=media(value2Length,value2);
  m2=media(valueLength,value);
  
  mod=moda(value2Length,value2);
  mod2=moda(valueLength,value);
  
  des=desviacion(value2Length,value2);
  des2=desviacion(valueLength,value);
  
  vrms1=vrms(value2Length,value2);
  vrms2=vrms(valueLength,value);
  
  
  
  Serial.print("Paciente sano");
  Serial.println();
  Serial.print("Media: ");
  Serial.println(m);
  maximo1,maximo2,maximo3,med=mediana(value2Length,value2);
  Serial.print("Mediana: ");
  Serial.println(med);
  Serial.print("Moda: ");
  Serial.println(mod);
  Serial.print("Desviacion: ");
  Serial.println(des);
  Serial.print("VRMS: ");
  Serial.println(vrms1);
  Serial.print("Valor pico: ");
  Serial.println(maximo1);
  d1=distance(value2Length,value2, maximo1,maximo3);
  Serial.print("Distancia normal: ");
  Serial.println(d1);
  delay(1000);
  
  Serial.print("Paciente con señal anormal");
  Serial.println();
  Serial.print("Media: ");
  Serial.println(m2);
  maximo1,maximo2,maximo3,med2=mediana(valueLength,value);
  Serial.print("Mediana: ");
  Serial.println(med2);
  Serial.print("Moda: ");
  Serial.println(mod2);
  Serial.print("Desviacion: ");
  Serial.println(des2);
  Serial.print("VRMS: ");
  Serial.println(vrms2);
  Serial.print("Valor pico: ");
  Serial.println(maximo1);
  d2=distance(value2Length,value2,maximo1,maximo2);
  Serial.print("Distancia anomala: ");
  Serial.println(d2);
  delay(1000);
}

void loop()
{

  int i = 0;      
  while (i < sizeof(value)) 

  {
    PORTD = pgm_read_byte_near(value + i);
    i++;
  }
}