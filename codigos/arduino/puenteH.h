class puenteH{
  //Clase que facilita el control de los motores al guardar todo en una clase
  public:
    //Guarda los pines del puente H y el de la potencia
    int Pines_Puente[2];
    int Pin_EN;

    puenteH(int pin1,int pin2, int pinEN){
      //Guardar los pines al declarar la clase
      Pines_Puente[0]=pin1;
      Pines_Puente[1]=pin2;
      Pin_EN=pinEN;

      //Declarar como OUTPUT
      pinMode(Pines_Puente[0],OUTPUT);
      pinMode(Pines_Puente[1],OUTPUT);
      pinMode(Pin_EN,OUTPUT);
    }
    
    //Lo único que necesitamos es darle la potencia que queremos al motor
    void move(int potencia){
      //Solo si es positivo, prendemos el primer pin del puenteH
      digitalWrite(Pines_Puente[0], (potencia>0));
      //Solo si es negativo, prendemos el segundo pin del puenteH
      digitalWrite(Pines_Puente[1], (potencia<0));
      //NOTA: Observar que si potencia==0, ambos se apagan

      //por último, actualizar el valor de la potencia, en valor absoluto para que tenga sentido
      analogWrite(Pin_EN, abs(potencia))
    }

}
