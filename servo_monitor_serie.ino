/*  Tarefa 01: Control de Servo con Potenciómetro e Pasos de 10 graos
Esta programación trata sobre cómo podemos controlar un servo mediante un potenciómetro. 
Para ello, lo más importante de esta programación es hacer la conversión del potenciómetro 
al servo para que se puedan entender; para ello, en el apartado void loop, 
se hace con la función map para que los dos componentes se puedan entender.
Tutor: Víctor M. Álvarez Pérez
Alumno: Ricardo García Pérez
Data: 26/02/2026
*/
#include <Servo.h>

Servo servochulon;

/* Declaramos las variables que usaremos; en este caso, serán donde están conectados el servo y el potenciómetro, 
además de la posición actual del servo y su posición anterior*/

int pinServo = 3; 
int pinPotenciometro = A5;
int angulo = 0;
int anguloAnterior = 0;
int lectura = 0;


/* En el 'void setup' indicamos al Arduino dónde está conectado el servo. 
   Aunque declaremos el pin, el Arduino no reconoce automáticamente qué componente 
   tiene conectado; por ello, especificamos que se trata de un servo.
   Despues, configuramos el monitor serie para mostrar la información 
   que pide la práctica.*/

void setup() { 

  servochulon.attach(pinServo);
  servochulon.write(0);
  Serial.begin(9600);
  Serial.println("Escribe: esquerda, diagonal esquerda, centro, diagonal dereita, dereita ou un numero de 0 a 180");
}

void loop() {

  if (Serial.available() > 0) { /*Hago esto para indicarle al Arduino que, si no detecta nada por el 
  monitor serie, continúe y verifique si hay cambios en el potenciómetro. 
  En cambio, si detecta algún carácter o valor, debe dirigirse al primer if que hay donde dependiendo de lo 
  escrito derecha, izquierda, centro que se mueva a la posición asignada*/
    
    String texto = Serial.readStringUntil('\n');
    texto.trim();
    texto.toLowerCase();
    angulo = -1;

    if (texto == "esquerda") {
      angulo = 0;
    } else 
      if (texto == "diagonal esquerda") {
      angulo = 45;
    } else 
      if (texto == "centro") {
      angulo = 90;
    } else 
      if (texto == "diagonal dereita") {
      angulo = 135;
    } else 
      if (texto == "dereita") {
      angulo = 180;
    } else {
      angulo = texto.toInt();
    
    }

    if (angulo >= 0 && angulo <= 180) {  /* aqui simplemente hacemos que si no es nada de lo anterior derecha, izquierda... 
    venga a este if para comprobar si es un nuemro del 0 al 180 y si no es ninguno */
    
      servochulon.write(angulo);
      Serial.print("Moviendo a: ");
      Serial.println(angulo);
    } else {
      Serial.println("Error, escribe un numero entre 0 y 180");
    }

 } 
  
  /* aqui simplemente lo que hacemos es con la funcion map convertir los valores del potenciometro al servo
  para que se puedan entender y que cuando se haga salga por el monitor serie que ponga que ese movimiento 
  sea por el servo y que lo ponga por el monitor serie que ese movimiento fue por el potenciometro y el angulo al cual fue*/
  
  
else {
    lectura = analogRead(pinPotenciometro);
    angulo = map(lectura, 0, 1023, 0, 180);
    angulo = (angulo / 10) * 10;

    if (angulo != anguloAnterior) {
      anguloAnterior = angulo;
      servochulon.write(angulo);
      Serial.print("Potenciometro: ");
      Serial.println(angulo);
      
      
  delay(6667); 
    }
  }
}
