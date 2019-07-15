\# First activity of CG UFPB. Alison R. M. Barreiro - 11328393 #Abstract Normally, graphs are defined through geometric primitives such as points, lines, circles, texts, etc. It may seem simple to draw a line in the video, however, this kind of routine is not as simple as it sounds. Given this, we will develop functions in conjunction with framwork, which makes writing in video memory to perform these tasks, and perform an analysis of improvements when possible, this is also important to create more efficient applications. This post consists of implementing raster algorithms for points and lines in C / C ++ language along with the GLUT and OpenGL libraries using the Framework previously made available by the teacher. #Introduction This article is about Activity 1 of the subject of Introduction to Computer Graphics, taught by Prof. Christian Pagot.

**Rasterizing a Point (Pixel) on the screen**

A point in computing, in this case, pixel, has the following properties:

  

*   Position in plan
  
*   Color

Each device (monitor) has its own hardware specifications, and the pixel size will depend on the graphic resolution and physical size of the device. Pixel manipulation operations are essential because from this manipulation, images are constructed or altered. In addition, we can construct graphical elements more complex than a point, but, there is a sequence of actions and algorithms so that they can be constructed.

1.  Function PutPixel();

The function rasterizes a point in the video memory, receiving as parameters the position of the pixel on the screen (x, y) and its color (RGBA). Each pixel occupies 4 bytes in the video memory, whose each byte corresponds to an RGBA value. The video memory can be represented as a linear vector, having 4 times the screen size of the device. With this, we get the following function:

**offset = (x + y \* Image\_Width) \* 4;**

Understanding this, let's use the pointer **FBptr**, which initially points to the beginning of memory (0,0), with it, we will be able to point the place where we will assign the color of the Pixel.

First, let's draw some random pixels on the screen, as we can see in **The image 1**.

> `void MyGlDraw(void) { PutPixel(100,100,cor1); }`

![screenshot-from-2017-02-20-234832](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-20-234832.png)  
Image 1 - Pontos aleatórios.

Na **Figura 2**, podemos observar a arte de que a matemática em conjunto com a computação gráfica pode proporcionar.

> void MyGlDraw(void) { PutPixel( rand()%512,rand()%512,cor1); }

![screenshot-from-2017-02-20-235426](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-20-235426.png)

Figura 2 - Rand.

**Rasterização de Linhas**

A rasterização de uma reta consiste em, determinar os pixels localizados entre um ponto inicial e um final, cuja, deve preencher este segmento de reta o mais uniforme possível, em um dispositivo (monitor), e pode ser, vertical, horizontal ou diagonal.

![screenshot-from-2017-02-21-003503](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-21-003503.png)

Figura 3 - rasterização.

Contudo, não é tao simples assim, pois no caso de uma reta diagonal podemos ter uma fraca densidade na linha, para que a densidade seja o mais uniforme possível, precisamos selecionar a maior quantidade de pixels possíveis entre os dois pixels extremos da reta, selecionando os pixels mais próximos.

Para o desenho de linhas, vamos utilizar o algoritmo de Bresenham, pois tem maior precisão nos resultados e na velocidade de execução, quando os seus extremos se localizam nos pixels **P1** e **P2** de coordenadas **(x1,y1)** e  **(x2,y2)**, respectivamente.

Este algoritmo utiliza apenas aritmética de inteiros, e vai incrementalmente calculando os pixeis que melhor se aproxima à reta ideal, e, portanto, permite um maior desempenho.  O algoritmo baseia-se no critério do ponto médio.

assumindo que o pixel que acabou de ser selecionado é C em(x ,y), e o próximo deve ser escolhido entre o pixel à direita superior **NE** e o pixel à direita inferior a **E**. Seja M o ponto intermediário entre os pixels, o que se faz é observar de que lado da reta está o ponto M, como podemos observar na **Figura 4**.  É fácil verificar que M está acima de **E** e está mais próximo da reta, Dessa forma, o teste do ponto médio permite a escolha do pixel mais próximo da reta, como podemos observar na **Figura 5**. Veja que assumindo uma distancia normalizada e igual a 1 (adimensional) entre os pixels adjacentes, tem-se com esse algoritmo um erro de no máximo ½ (adimensional), que é a metade da distância entre dois pixels vizinhos da mesma coluna.

![screenshot-from-2017-02-22-231919](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-22-231919.png)

Figura 4 - Escolha do pixel.

![screenshot-from-2017-02-22-233915](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-22-233915.png)

Figura 5 - Pixel escolhido.

Após a decisão de qual pixel será considerado, deve-se atualizar e utilizar o valor do algoritmo de decisão. Se foi o último pixel escolhido, M será incrementado somente na direção x . Têm-se

então as seguintes igualdades:

Se escolha for E (**Figura 5**):

**dold =α (xc +1)+β( yc + 1/2)+ γ**

**dnew =α ( xc +2)+β( yc +1/2 )+ γ**

**dnew − dold → dnew = dold +α**

Se escolha for NE (**Figura 6**):

**dold =α ( xc +1)+β( yc + 1/2)+ γ**

**dnew =α (xc +2)+β( yc + 1/2)+ γ**

**dnew −dold → dnew =dold +α +β**

![screenshot-from-2017-02-22-230932](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-22-230932.png)

 Figura 6 - Ponto NE.

Com esses valores em mãos, o próximo passo é desenvolver realmente o algoritmo. Na

**figura 7**, uma versão simplificada do Algoritmo de Bresenham. Para operações mais complexas, vamos escrever o Bresenham melhorado, na **Figura 10**, cuja, inverte os pontos.

Sequência de passos para Bresenham com parâmetros de entrada: (x1,y1) e (x2,y2). 1. Calcula-se **( DX = X2 -X1 ) e ( DY = Y2 -Y1 )** . 2. Calculam-se as variáveis auxiliares: **2DY** e **2DY-2DX**. 3. Coloca-se nas variáveis de trabalho o ponto inicial: **X <- X1 e Y<-Y1**. 4. Plota-se o ponto (x,y). 5. Calcula-se o parâmetro de decisão: **P=2DY – DX**. 6. Se **P** for negativo, então **X <-X+1, P <- P+2DY** e vai para o passo 8. 7. Se **P** for positivo ou zero, então: **X <- X+1, Y <- Y+1 e P <- P+2DY – 2DX**. 8. Repetem-se os passos 6 a 7 até que o ponto (X 2 , Y 2 ) seja alcançado.

Função DrawLine();

Primeiramente, utilizamos o algoritmo padrão de Bresenham **Figura 7**, podemos observar na **Figura 8**, o mesmo apresentou o problema não não conseguir realizar as retas em diferentes octantes, então precisamos melhorar.

> void MyGlDraw(void) { MidPointLine(50, 400, 0, 300,cor1);
> 
> }

![screenshot-from-2017-02-22-230629](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-22-230629.png)

Figura 7 - Bresenham.

![breseham-bugado-20-do-07](https://barreirocg.files.wordpress.com/2017/02/breseham-bugado-20-do-07.png)

Figura 8 - Bresenham padrão.

De fato, o algoritmo de Bresenham, neste caso, utilizando este framwork, desenha apenas no primeiro octante. Então, precisamos aprimorar o código para utilização neste framwork, Podemos observar o novo resultado na **Figura 11**.

> void MyGlDraw(void) { DrawLine(512,0,0,512,cor1); DrawLine(256,0,256,512,cor2); DrawLine(0,0,512,512,cor3); DrawLine(0,256,512,256,cor4);
> 
> }

![brline001](https://barreirocg.files.wordpress.com/2017/02/brline001.png)

Figura 9 - Octantes.

![screenshot-from-2017-02-23-005543](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-005543.png)

Figura 10 - Algoritmo Bresenham para todos os octantes.

![screenshot-from-2017-02-23-005827](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-005827.png)

Figura 11 - Bresenham para todos os octantes.

**Interpolação Linear de Cor**

A interpolação de cor é comum e constantemente utilizado na computação gráfica, utilizado principalmente na rasterização de objetos, neste trabalho vamos utilizar na implementação do algoritmo de Bresenham na função DrawLine. Precisamos levar em conta, primeiramente, o tamanho da reta, para interpolação de forma correta, isso é de extra importância, pois não queremos que seja feita uma interpolação incorreta. Vamos dar uma visão geral dos métodos de interpolação para posteriormente detalhar, e mais tarde fazer um estudo de casos. A interpolação é uma técnica que permite "preencher uma lacuna" entre dois números. A maioria das APIs expõe a interpolação linear baseada em três parâmetros: o ponto inicial **X1,Y1**, e o ponto final **X2, Y2** e um valor size entre 0 e 1 que se move ao longo do segmento que os conectou: **cor = (X1,Y1) + ((X2,Y2)-(X1,Y1)) \* size** Quando **t = 1**, então é retornado, **(X1,Y1) + ((X2,Y2)-(X1,Y1)) = (X2,Y2)**. A beleza desta fórmula é que é fácil de entender, eficiente de implementar, e funciona em qualquer dimensão. As dimensões só requer ler de forma independente os componentes X e Y. Sempre retorna pontos na linha que liga **(X1,Y1)** e **(X2,Y2)**, independentemente do número de dimensões.

A ideia principal é calcular primeiramente o tamanho da reta com relação aos seus pontos, para isso usamos a Função: **tamanho\_final =** **√(((x2-x1)\*(x2-x1))+((y2-y1)\*(y2-y1)));** Tendo o tamanho da reta em mãos, calculamos a relação dela pelo tamanho da reta atualmente, ou seja, uma divisão de tamanho inicial pelo final, com isso temos uma variação entre 0~1; Então obtemos um simples calculo incremental, visto que o mesmo encontra-se em loop no for, **size =** **(tamanho\_atual++)/tamanho\_final;** ![screenshot-from-2017-02-23-120825](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-120825.png)

Figura 12 - Função Interpolar.

Agora podemos calcular a cor de cada pixel, enviado para a função PutPixel, como podemos observar na **Figura 13**.

> void MyGlDraw(void) { DrawLine(512,0,0,512,red,blue); DrawLine(256,0,256,512,blue,red); DrawLine(0,0,512,512,gree,pastel); DrawLine(0,256,512,256,pastel,gree);
> 
> }

> void DrawLine(int x1, int y1, int x2, int y2,colorRGBA cor1,colorRGBA cor2){
> 
> **...**
> 
> **tamanho\_atual++;                                                                                                                               cor = interpolar(cor1,cor2, tamanho\_atual/tamanho\_final);** **PutPixel(xp,yp,cor);**
> 
> **...**
> 
> }

![screenshot-from-2017-02-23-114450](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-114450.png)

Figura 13 - DrawLine com interpolação de Cor.

**Triângulos**

Agora de forma trivial, vamos desenhar um triângulo na tela, para isso, basta informar as suas arestas e juntamente com a Função DrawLine temos um triângulo desenhado na tela, como podemos observar na **Figura 15**.

O algoritmo é simples, a função DrawTriangle recebe seus vértices e e passa função DrawLine, cuja desenha as três linhas.

![screenshot-from-2017-02-23-131326](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-131326.png)

Figura 14 - DrawTriangle com interpolação de Cor.

> void MyGlDraw(void) { DrawTriangle(128,128,384,384,128,384,red,blue,gree); DrawTriangle(160,128,384,352,384,128,red,blue,gree); DrawTriangle(200,100,300,100,250,50,red,blue,gree);
> 
> }

![screenshot-from-2017-02-23-130722](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-130722.png)

Figura 15 - Desenhando triângulos.

**Desenhando uma curva com Interpolação de Cor**

O  cálculo dos dessa circunferência é utilizando diretamente no calculo de círculos,  é necessário encontrar um algoritmo, que, à semelhança do que se fez para a reta, mas tente minimizar as operações e calcule o raio da circunferência. É claro, deve utilizar a natureza simétrica, usamos o um algoritmo para o ponto de decisão:

> void drawCurve(int radius) {
> 
> ...
> 
> if(d < 0) {                                                                                                                                                        // escolher E                                                                                                                                                   d += 2 \* x + 3;                                                                                                                                                 } else {                                                                                                                                             //Escolhe NE                                                                                                                                                 d += 2 \* (x-y) + 5;                                                                                                                                              --y;
> 
> }
> 
> ...
> 
> }

Com isso, obtemos o seguinte resultado com relação ao framwork utilizado, **Figura 16**:

![screenshot-from-2017-02-23-152711](https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-152711.png)

Figura 16- drawCurve.

**Resultados e Discussão**

A rasterização de pontos proporciona uma infinidade de possíbilidades em computação gráfica, Um algoritmo de traçado de  retas, o Bresenham é de grande utilidade e eficiência.

Principais dificuldades foi na implementação do algoritmo de Bresenham e interpolação de cor, a principal dificuldade com Bresenham foi com relação aos oito octantes, depois de muita pesquisa e leitura, foi possível escrever um algoritmo valido para todos os octantes.

Com relação a interpolação de cor. Seguindo o Foley, e as informações sobre interpolação Linear, apresentava alguns erros e simplesmente não funcionava, visto que o calculo final sempre resultava em 0.00001, então foi feito mudado todo o algoritmo, e apenas adicionando uma interpolação incremental com relação ao tamanho da reta e o tamanho atual da reta.

**Considerações Finais**

A rasterização de pontos é muito interessante e ambre porta para intendimentos de modelagem e cálculos para desenho gráficos, podemos, por exemplo, utilizar uma ferramenta gráfica para desenhar, exportar pontos e criar uma desenho, utilizando a rasterização de pontos, de fato, existe diversas ferramentas para isso, mas o ideal é entender como funciona.

**Referências**

1.  Anotações de Aula do Prof. Christian Azambuja Pagot (2016.2)
2.  Slides de Disciplina CG 2016.2 Disponibilizado no SIGAA UFPB (2016.2)
3.  http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/ (02/2017)
4.  http://www.demic.fee.unicamp.br/~jeff/ArquivosIndex/Bresenham (02/2017)
