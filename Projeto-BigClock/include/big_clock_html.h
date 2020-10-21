static const char RELOGIO_page[] PROGMEM = R"=====(
<!DOCTYPE html><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
      html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
      .button {background-color: blue; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 40px; margin: 0px; cursor: pointer;}
      .button2 {background-color: #77878A;}
    </style>
  </head>
  <hr>
  <h1>BIG CLOCK v1.0 by TuLiO</h1><br>
  <p><a href="/cron"><button class="button">CRONOMETRO</button></a></p>
  <hr>
</html>
)=====";

static const char CRONOMETRO_page[] PROGMEM = R"=====(
<!DOCTYPE html><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
      html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
      .button {background-color: blue; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 40px; margin: 0px; cursor: pointer;}
      .button2 {background-color: #77878A;}
    </style>
  </head>
  <hr>
  <h1>CRONOMETRAR</h1><br>
  <p><a href="/cron/play"><button class="button">INICIAR</button></a></p><br>
  <p><a href="/cron/reset"><button class="button">ZERAR</button></a></p><br>
  <p><a href="/"><button class="button">VOLTAR</button></a></p><br>
  <hr>
</html>
)=====";