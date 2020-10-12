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

char TIMER_page[] PROGMEM = R"=====(
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
    .button {background-color: blue; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 40px; margin: 0px; cursor: pointer;}
    .button2 {background-color: #77878A;}
    .font {font-size: 40px}
  </style>
</head>
<body><hr>
    <h1>TIMER</h1><br>
    <form action=/timer method="post">
        <p class="font"><input class="font" type="number" id="timer_min" name="timer_min" min="0" max="99" style="width: 80px;" value="">:<input class="font" type="number" id="timer_seg" name="timer_seg" min="0" max="59" style="width: 80px;" value=""></p>
        <p class="font">min:seg</p>
        <br><input class="button" type="submit" value="INICIAR">
    </form>
    <br><p><a href="/"><button class="button">VOLTAR</button></a></p><br>
<hr></body>
</html>
)=====";