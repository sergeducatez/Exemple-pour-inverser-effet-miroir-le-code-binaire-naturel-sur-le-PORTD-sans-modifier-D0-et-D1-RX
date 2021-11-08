//**************************************************************************************************************************************************************************
// Démo : Exemple pour inverser (effet miroir) le code binaire naturel sur le PORTD sans modifier D0 et D1 (RX et TX) - Arduino Nano
//**************************************************************************************************************************************************************************
// Auteur : Serge Ducatez - 11/2021
// https://www.youtube.com/channel/UCyGEFYW18IZKpe4uPgp9b8g/videos
// https://www.facebook.com/serge.ducatez.7/photos_albums
//**************************************************************************************************************************************************************************

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (uint8_t Octet_BinaireNaturel = 0b00000001; Octet_BinaireNaturel <= 0b00111111; Octet_BinaireNaturel++)
  {
    Serial.print("Octet_BinaireNaturel = "); Serial.print(Octet_BinaireNaturel << 2, BIN);
    Serial.print(" ");
    Serial.print("Octet_Miroir = "); Serial.println(FonctionMiroir_PortD(Octet_BinaireNaturel << 2), BIN);
    
  }
  while(1);
}

uint8_t FonctionMiroir_PortD (uint8_t Octet_Original)
{
  uint8_t Octet_Miroir = 0b00000000;
  const uint8_t Masque1 = 0b00000100;
  
  for (int Bit_Octet_Original_n = 7; Bit_Octet_Original_n > 1; Bit_Octet_Original_n--)
  {
    if ((Octet_Original & (1 << Bit_Octet_Original_n)) >> Bit_Octet_Original_n == 1)
    {
      Octet_Miroir |= (Octet_Miroir | (Masque1 << ((6 - Bit_Octet_Original_n) + 1)));
    }
    else if ((Octet_Original & (1 << Bit_Octet_Original_n)) >> Bit_Octet_Original_n == 0)
    {
      Octet_Miroir |= (Octet_Miroir & (~Masque1 << ((6 - Bit_Octet_Original_n) + 1)));
    }
  }
  
  return (Octet_Miroir);
}
