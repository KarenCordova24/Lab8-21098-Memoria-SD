//Laboratorio 8- Karen Córdova- 21098

//************************************************************************************************
//LIBRERÍAS 
//************************************************************************************************/
#include <SPI.h>
#include <SD.h>

//************************************************************************************************
//FILES DEL MICRO SD 
//************************************************************************************************/
File Barbie;
File LionK;
File TinkerB;
File Post;

//************************************************************************************************
//VARIABLES GLOBALES  
//************************************************************************************************/

int val = 0;
int FLAG = 0;
char option;
const int altura = 10;
const int ancho = 20;
char obra[altura][ancho];

//************************************************************************************************
//DEFINICIÓN DE PINES 
//************************************************************************************************/
const int LEDR = RED_LED;
const int LEDV = GREEN_LED;
const int pushM = PUSH1;

//************************************************************************************************
//PROTOTIPOS DE FUNCION 
//************************************************************************************************/

void drawing ();
void guardar ();

//************************************************************************************************
//CONFIGURACION 
//************************************************************************************************/

void setup() {
  SPI.setModule(0);
  Serial.begin(115200);
  pinMode(pushM, INPUT_PULLUP);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDV, OUTPUT);
  pinMode(12, OUTPUT);

  if (!SD.begin(12)) {
    Serial.println("¡Inicialización fallida!");
    return;
  }
  Serial.println("¡Inicialización completa!");
}

//************************************************************************************************
//LOOP PRINCIPAL 
//************************************************************************************************/

void loop() {
  int Buttonstate1 = digitalRead(pushM);

  // Si el botón está presionado
  if (Buttonstate1 == LOW) {
    FLAG = 1;
  } else {
    // Si el botón se ha soltado
    if (FLAG == 1) {
      FLAG = 0;
      // Mostrar el menú de selección de peliculas 
      
      Serial.print("        ***  MENU DE SELECCIÓN  ***\n     ");
      Serial.print(" Ingrese el número de la película que desee ver \n ");
      Serial.print("1) Barbie \n");
      Serial.print(" 2) Rey Leon \n ");
      Serial.print("3) Tinker Bell \n ");
      Serial.print("4) Drawing  \n ");
      Serial.print("5) Mostrar dibujo  \n ");
    }
  }

  // Procesar la entrada serial
  while (Serial.available() > 0) {
    option = Serial.read();

    if (option >= '0' && option <= '5') {
      switch (option) {
 
        case '1':
          // Mostrar Barbie
          digitalWrite(LEDR, HIGH);   //Enciende LED ROJO (indicador que esta mostrando el archivo)
          delay(1000);
          Serial.println("\n...PELÍCULA 1: BARBIE ...");
          Barbie = SD.open("Barbie.txt");    //Abre el archivo de Barbie
          if (Barbie) {
            Serial.println("Barbie.txt");  //Imprime el contenido en el monitor serial 
            while (Barbie.available()) {  //Mientras que haya datos lee y envía los datos en el monitor serial
              Serial.write(Barbie.read());
            }
            Barbie.close();  //Cierra el archivo 
            digitalWrite(LEDR, LOW);
            delay(250);
          }
           Serial.println("Regresando al Menu Principal...");
           FLAG = 1;
          break;
        case '2':
          // Mostrar Rey Leon
          digitalWrite(LEDR, HIGH);  //Enciende LED ROJO Y VERDE (indicador que esta mostrando el archivo)
          digitalWrite(LEDV, HIGH);
          delay(1000);
          Serial.println("\nPELÍCULA 2:... LION KING...");
          LionK = SD.open("LionK.txt");  //Abre el archivo de LionKing
          if (LionK) {
            Serial.println("LionK.txt");
            while (LionK.available()) {   //Mientras que haya datos lee y envía los datos en el monitor serial
              Serial.write(LionK.read());
            }
            LionK.close();  //Cierra el archivo 
            digitalWrite(LEDR, LOW);
            digitalWrite(LEDV, LOW);
            delay(250);
          }
           Serial.println("Regresando al Menu Principal...");
          FLAG = 1;
          break;
        case '3':
          // Mostrar Tinker Bell
          digitalWrite(LEDV, HIGH); //Enciende LED VERDE (indicador que esta mostrando el archivo)
          delay(1000);
          Serial.println("...PELÍCULA 3: TINKERBELL...");
          TinkerB = SD.open("TinkerB.txt"); //Abre el archivo de TinkerBell
          if (TinkerB) {
            Serial.println("\nTinkerB.txt");
            while (TinkerB.available()) {  //Mientras que haya datos lee y envía los datos en el monitor
              Serial.write(TinkerB.read());
            }
            TinkerB.close();  //Cierra el archivo 
            digitalWrite(LEDV, LOW);
            delay(250);
          }
           Serial.println("\nRegresando al Menu Principal...");
          FLAG = 1;
          break;
        case '4':
          // Dibujar y guardar obra
          drawing();
          guardar();
          
           Serial.println("Regresando al Menu Principal...");
          FLAG = 1;
          break;
          
       case '5':
          Post = SD.open("postlab.txt");  //Abre el archivo en el microSD
          if (Post) {
            Serial.println("postlab.txt:");  //Imprime el conitenido del archivo Postlab
            while (Post.available()) {  // Lee y envia datos del archivo al monitor serial
              Serial.write(Post.read());
            }
            Post.close();  //Cierra el archivo 
          } else {
            Serial.println("error opening postlab.txt");
          }
           Serial.println("Regresando al Menu Principal...");
          FLAG = 1;
          break;
       
      }
    }
  }
}

//************************************************************************************************
//FUNCIONES  
//************************************************************************************************/

void drawing() {
   // Indicar cómo dibujar y qué significa 'X' y ' '
   Serial.println("Dibuja tu obra (utiliza 'X' para dibujar y ' ' para dejar espacios entre carácter, y 'D' para terminar): ");
   Serial.println("Tienes espacio para dibujar de 20 columnas y 10 filas");

    //Inicializar la matriz "obra" con espacios en blanco
   for (int i = 0; i < altura; i++) {
        for (int j = 0; j < ancho; j++) {
            obra[i][j] = ' ';
        }
    }

  //Iterar a traves de la matriz "obra"  para que pueda dibujar 
   for (int i = 0; i < altura; i++) {
        for (int j = 0; j < ancho; j++) {
            while (Serial.available() == 0) {
                // Espera a que el usuario ingrese caracteres
            }
            char caracter = Serial.read();
            if (caracter == 'X' || caracter == 'x') {  //Dibuja usando "X"
                obra[i][j] = 'X';
            } else if (caracter == 'D' || caracter == 'd') {  //Si presiona "D" su dibujo termina
                // Terminar el dibujo
                Serial.println("\nDibujo terminado.");
                return;
            }
            Serial.print(obra[i][j]);  //Muestra el caracter en el monitor serial 
        }
        Serial.println(); //Cambiar de linea despues de una fila 
    }   
}

void guardar() {
  // Abre el archivo en modo escritura
  Post = SD.open("postlab.txt", FILE_WRITE);

  if (Post) {
    for (int i = 0; i < altura; i++) {  //Itera a traves de la matriz "obra" y escribe su contenido en el monitor serial
      for (int j = 0; j < ancho; j++) {
        Post.print(obra[i][j]);
      }
      Post.println();
    }

    Post.close();
    Serial.println("Imagen guardada correctamente en postlab.txt");
  } else {
    Serial.println("No se encontró el archivo para escritura.");
  }
}
