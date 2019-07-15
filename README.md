# First activity of CG UFPB. 
Alison R. M. Barreiro - 11328393


#Abstract

Normally, graphs are defined through geometric primitives such as points, lines, circles, texts, etc. It may seem simple to draw a line in the video, however, this kind of routine is not as simple as it sounds. Given this, we will develop functions in conjunction with framwork, which makes writing in video memory to perform these tasks, and perform an analysis of improvements when possible, this is also important to create more efficient applications. This post consists of implementing raster algorithms for points and lines in C / C ++ language along with the GLUT and OpenGL libraries using the Framework previously made available by the teacher.

#Introduction

This article is about Activity 1 of the subject of Introduction to Computer Graphics, taught by Prof. Christian Pagot.

<p style="text-align: justify;"><strong>Rasterizing a Point (Pixel) on the screen</strong></p>
<p style="text-align: justify;">A point in computing, in this case, pixel, has the following properties:</p>
<br>
<ul style="text-align: justify;">
	<li>Position in plan</li><br>
	<li>Color</li>
</ul>
<p style="text-align: justify;">Each device (monitor) has its own hardware specifications, and the pixel size will depend on the graphic resolution and physical size of the device.
Pixel manipulation operations are essential because from this manipulation, images are constructed or altered.
In addition, we can construct graphical elements more complex than a point, but, there is a sequence of actions and algorithms so that they can be constructed.</p>

<ol style="text-align: justify;">
	<li>Function PutPixel();</li>
</ol>
<p style="text-align: justify;">The function rasterizes a point in the video memory, receiving as parameters the position of the pixel on the screen (x, y) and its color (RGBA). Each pixel occupies 4 bytes in the video memory, whose each byte corresponds to an RGBA value. The video memory can be represented as a linear vector, having 4 times the screen size of the device. With this, we get the following function:</p>
<p style="text-align: justify;"><strong>offset = (x + y * Image_Width) * 4;</strong></p>
<p style="text-align: justify;">Understanding this, let's use the pointer <b>FBptr</b>, which initially points to the beginning of memory (0,0), with it, we will be able to point the place where we will assign the color of the Pixel.</p>
<p style="text-align: justify;">First, let's draw some random pixels on the screen, as we can see in <strong>The image 1</strong>.</p>

<blockquote>
void MyGlDraw(void) { <br>
		PutPixel(100,100,cor1);<br>
	}
	
</blockquote><br>
	<center><p style="text-align: center;"><img class="aligncenter wp-image-33 size-full" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-20-234832.png" alt="screenshot-from-2017-02-20-234832" width="512" height="540" />Figura 1 - Pontos aleatórios.</p></center>

<p style="text-align: justify;">Na <strong>Figura 2</strong>, podemos observar a arte de que a matemática em conjunto com a computação gráfica pode proporcionar.</p>
	
<blockquote>
	void MyGlDraw(void) {
PutPixel( rand()%512,rand()%512,cor1);

}
</blockquote>

<p style="text-align: justify;"><img class="aligncenter wp-image-34 size-full" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-20-235426.png" alt="screenshot-from-2017-02-20-235426" width="512" height="540" /></p>
<p style="text-align: center;">Figura 2 - Rand.</p>
<p style="text-align: justify;"><strong>Rasterização de Linhas</strong></p>
<p style="text-align: justify;">A rasterização de uma reta consiste em, determinar os pixels localizados entre um ponto inicial e um final, cuja, deve preencher este segmento de reta o mais uniforme possível, em um dispositivo (monitor), e pode ser, vertical, horizontal ou diagonal.</p>
<p style="text-align: justify;"><img class="alignnone size-full wp-image-42" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-21-003503.png" alt="screenshot-from-2017-02-21-003503" width="1108" height="380" /></p>
<p style="text-align: justify;">Figura 3 - rasterização.</p>
<p style="text-align: justify;">Contudo, não é tao simples assim, pois no caso de uma reta diagonal podemos ter uma fraca densidade na linha, para que a densidade seja o mais uniforme possível, precisamos selecionar a maior quantidade de pixels possíveis entre os dois pixels extremos da reta, selecionando os pixels mais próximos.</p>
<p style="text-align: justify;">Para o desenho de linhas, vamos utilizar o algoritmo de Bresenham, pois tem maior precisão nos resultados e na velocidade de execução, quando os seus extremos se localizam nos pixels <strong>P1</strong> e <strong>P2</strong> de coordenadas <strong>(x1,y1)</strong> e  <strong>(x2,y2)</strong>, respectivamente.</p>

<div dir="ltr" style="text-align: justify;">Este algoritmo utiliza apenas aritmética de inteiros, e vai incrementalmente calculando os pixeis que melhor se aproxima à reta ideal, e, portanto, permite um maior desempenho.  O algoritmo baseia-se no critério do ponto médio.</div>
<div dir="ltr" style="text-align: justify;">assumindo que o pixel que acabou de ser selecionado é C em(x ,y), e o próximo deve ser escolhido entre o pixel à direita superior <strong>NE</strong> e o pixel à direita inferior a <strong>E</strong>. Seja M o ponto intermediário entre os pixels, o que se faz é observar de que lado da reta está o ponto M, como podemos observar na <strong>Figura 4</strong>.  É fácil verificar que M está acima de <strong>E</strong> e está mais próximo da reta, Dessa forma, o teste do ponto médio permite a escolha do pixel mais próximo da reta, como podemos observar na <strong>Figura 5</strong>. Veja que assumindo uma distancia normalizada e igual a 1 (adimensional) entre os pixels adjacentes, tem-se com esse algoritmo um erro de no máximo ½ (adimensional), que é a metade da distância entre dois pixels vizinhos da mesma coluna.</div>
<div dir="ltr" style="text-align: justify;"></div>
<div dir="ltr" style="text-align: justify;"><img class="size-full wp-image-54 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-22-231919.png" alt="screenshot-from-2017-02-22-231919" width="760" height="520" /></div>
<div dir="ltr" style="text-align: center;">Figura 4 - Escolha do pixel.</div>
<div dir="ltr" style="text-align: justify;"><img class="alignnone size-full wp-image-56" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-22-233915.png" alt="screenshot-from-2017-02-22-233915" width="917" height="497" /></div>
<div dir="ltr" style="text-align: center;">Figura 5 - Pixel escolhido.</div>
<div dir="ltr" style="text-align: justify;"></div>
<div dir="ltr" style="text-align: justify;">
<div dir="ltr">Após a decisão de qual pixel será considerado, deve-se atualizar e utilizar o valor do algoritmo de decisão. Se foi o último pixel escolhido, M será incrementado somente na direção x . Têm-se</div>
<div dir="ltr">então as seguintes igualdades:</div>
<div dir="ltr">Se escolha for E (<strong>Figura 5</strong>):</div>
</div>
<div dir="ltr" style="text-align: center;"><strong>d<span style="text-decoration: underline;">old</span> =α (x<span style="text-decoration: underline;">c</span> +1)+β( y<span style="text-decoration: underline;">c</span> + 1/2)+ γ</strong></div>
<div dir="ltr" style="text-align: center;"><strong>d<span style="text-decoration: underline;">new</span> =α ( <span style="text-decoration: underline;">xc</span> +2)+β( y<span style="text-decoration: underline;">c</span> +1/2 )+ γ</strong></div>
<div dir="ltr" style="text-align: center;"><strong>d<span style="text-decoration: underline;">new</span> − d<span style="text-decoration: underline;">old</span> → d<span style="text-decoration: underline;">new</span> = d<span style="text-decoration: underline;">old</span> +α</strong></div>
<div dir="ltr" style="text-align: justify;">Se escolha for NE (<strong>Figura 6</strong>):</div>
<div dir="ltr" style="text-align: center;"><strong>d<span style="text-decoration: underline;">old</span> =α ( x<span style="text-decoration: underline;">c</span> +1)+β( y<span style="text-decoration: underline;">c</span> + 1/2)+ γ</strong></div>
<div dir="ltr" style="text-align: center;"><strong>d<span style="text-decoration: underline;">new</span> =α (x<span style="text-decoration: underline;">c</span> +2)+β( y<span style="text-decoration: underline;">c</span> + 1/2)+ γ</strong></div>
<div dir="ltr" style="text-align: center;"><strong>d<span style="text-decoration: underline;">new</span> −d<span style="text-decoration: underline;">old</span> → d<span style="text-decoration: underline;">new</span> =d<span style="text-decoration: underline;">old</span> +α +β</strong></div>
<div dir="ltr" style="text-align: justify;"></div>
<div dir="ltr" style="text-align: justify;"><img class="alignnone size-full wp-image-53" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-22-230932.png" alt="screenshot-from-2017-02-22-230932" width="761" height="598" /></div>
<div dir="ltr" style="text-align: center;"> Figura 6 - Ponto NE.</div>
<div dir="ltr" style="text-align: justify;">
<div dir="ltr" style="text-align: left;">Com esses valores em mãos, o próximo passo é desenvolver realmente o algoritmo. Na</div>
<div dir="ltr" style="text-align: left;"><strong>figura 7</strong>, uma versão simplificada do Algoritmo de Bresenham. Para operações mais complexas, vamos escrever o Bresenham melhorado, na <strong>Figura 10</strong>, cuja, inverte os pontos.</div>
</div>
<div dir="ltr" style="text-align: justify;">Sequência de passos para Bresenham com parâmetros de entrada: (x1,y1) e (x2,y2).
1. Calcula-se <strong>( DX = X2 -X1 ) e ( DY = Y2 -Y1 )</strong> .
2. Calculam-se as variáveis auxiliares: <strong>2DY</strong> e <strong>2DY-2DX</strong>.
3. Coloca-se nas variáveis de trabalho o ponto inicial: <strong>X <- X1 e Y<-Y1</strong>.
4. Plota-se o ponto (x,y).
5. Calcula-se o parâmetro de decisão: <strong>P=2DY – DX</strong>.
6. Se <strong>P</strong> for negativo, então <strong>X <-X+1, P <- P+2DY</strong> e vai para o passo 8.
7. Se <strong>P</strong> for positivo ou zero, então: <strong>X <- X+1, Y <- Y+1 e P <- P+2DY – 2DX</strong>.
8. Repetem-se os passos 6 a 7 até que o ponto (X 2 , Y 2 ) seja alcançado.</div>
<p style="text-align: justify;">Função DrawLine();</p>
<p style="text-align: justify;">Primeiramente, utilizamos o algoritmo padrão de Bresenham <strong>Figura 7</strong>, podemos observar na <strong>Figura 8</strong>, o mesmo apresentou o problema não não conseguir realizar as retas em diferentes octantes, então precisamos melhorar.</p>

<blockquote>
<p style="text-align: left;"><span style="color: #339966;">void</span> MyGlDraw(<span style="color: #339966;">void)</span> {
MidPointLine(<span style="color: #ff00ff;">50</span>, <span style="color: #ff00ff;">400</span>, <span style="color: #ff00ff;">0</span>, 300,cor1);</p>
<p style="text-align: left;">}</p>
</blockquote>
<p style="text-align: justify;"><img class="size-full wp-image-52 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-22-230629.png" alt="screenshot-from-2017-02-22-230629" width="582" height="512" /></p>
<p style="text-align: center;">Figura 7 - Bresenham.</p>
<p style="text-align: justify;"><img class="size-full wp-image-44 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/breseham-bugado-20-do-07.png" alt="breseham-bugado-20-do-07" width="512" height="540" /></p>
<p style="text-align: center;">Figura 8 - Bresenham padrão.</p>
<p style="text-align: justify;">De fato, o algoritmo de Bresenham, neste caso, utilizando este framwork, desenha apenas no primeiro octante. Então, precisamos aprimorar o código para utilização neste framwork, Podemos observar o novo resultado na <strong>Figura 11</strong>.</p>

<blockquote>
<p style="text-align: left;"><span style="color: #339966;">void</span> MyGlDraw(<span style="color: #339966;">void)</span> {
DrawLine(<span style="color: #ff00ff;">512</span>,<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">512</span>,cor1);
DrawLine(<span style="color: #ff00ff;">256</span>,<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">256</span>,<span style="color: #ff00ff;">512</span>,cor2);
DrawLine(<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">512</span>,<span style="color: #ff00ff;">512</span>,cor3);
DrawLine(<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">256</span>,<span style="color: #ff00ff;">512</span>,<span style="color: #ff00ff;">256</span>,cor4);</p>
<p style="text-align: left;">}</p>
</blockquote>
<p style="text-align: justify;"><img class="size-full wp-image-61 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/brline001.png" alt="brline001" width="248" height="246" /></p>
<p style="text-align: center;">Figura 9 - Octantes.</p>
<p style="text-align: center;"><img class="alignnone size-full wp-image-60" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-005543.png" alt="screenshot-from-2017-02-23-005543" width="622" height="922" /></p>
<p style="text-align: center;">Figura 10 - Algoritmo Bresenham para todos os octantes.</p>
<p style="text-align: left;"><img class="size-full wp-image-62 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-005827.png" alt="screenshot-from-2017-02-23-005827" width="512" height="540" /></p>
<p style="text-align: center;">Figura 11 - Bresenham para todos os octantes.</p>
<p style="text-align: justify;"><strong>Interpolação Linear de Cor</strong></p>
<p style="text-align: justify;">A interpolação de cor é comum e constantemente utilizado na computação gráfica, utilizado principalmente na rasterização de objetos, neste trabalho vamos utilizar na implementação do algoritmo de Bresenham na função DrawLine.
Precisamos levar em conta, primeiramente, o tamanho da reta, para interpolação de forma correta, isso é de extra importância, pois não queremos que seja feita uma interpolação incorreta. Vamos dar uma visão geral dos métodos de interpolação para posteriormente detalhar, e mais tarde fazer um estudo de casos.
A interpolação é uma técnica que permite "preencher uma lacuna" entre dois números. A maioria das APIs expõe a interpolação linear baseada em três parâmetros: o ponto inicial <strong>X1,Y1</strong>, e o ponto final <strong>X2, Y2</strong> e um valor size entre 0 e 1 que se move ao longo do segmento que os conectou: <strong>cor = (X1,Y1) + ((X2,Y2)-(X1,Y1)) * size</strong>
Quando <strong>t = 1</strong>, então é retornado, <strong>(X1,Y1) + ((X2,Y2)-(X1,Y1)) = (X2,Y2)</strong>. A beleza desta fórmula é que é fácil de entender, eficiente de implementar, e funciona em qualquer dimensão. As dimensões só requer ler de forma independente os componentes X e Y. Sempre retorna pontos na linha que liga <strong>(X1,Y1)</strong> e <strong>(X2,Y2)</strong>, independentemente do número de dimensões.</p>
A ideia principal é calcular primeiramente o tamanho da reta com relação aos seus pontos, para isso usamos a Função:<strong> tamanho_final =</strong> <strong>√(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));</strong>
Tendo o tamanho da reta em mãos, calculamos a relação dela pelo tamanho da reta atualmente, ou seja, uma divisão de tamanho inicial pelo final, com isso temos uma variação entre 0~1;
Então obtemos um simples calculo incremental, visto que o mesmo encontra-se em loop no for, <strong>size =</strong> <strong>(tamanho_atual++)/tamanho_final;</strong>

<img class="alignnone size-full wp-image-65 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-120825.png" alt="screenshot-from-2017-02-23-120825" width="592" height="173" />
<p style="text-align: center;">Figura 12 - Função Interpolar.</p>
<p style="text-align: left;">Agora podemos calcular a cor de cada pixel, enviado para a função PutPixel, como podemos observar na <strong>Figura 13</strong>.</p>

<blockquote>
<p style="text-align: left;"><span style="color: #339966;">void</span> MyGlDraw(<span style="color: #339966;">void)</span> {
DrawLine(<span style="color: #ff00ff;">512</span>,<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">512</span>,red,blue);
DrawLine(<span style="color: #ff00ff;">256</span>,<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">256</span>,<span style="color: #ff00ff;">512</span>,blue,red);
DrawLine(<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">512</span>,<span style="color: #ff00ff;">512</span>,gree,pastel);
DrawLine(<span style="color: #ff00ff;">0</span>,<span style="color: #ff00ff;">256</span>,<span style="color: #ff00ff;">512</span>,<span style="color: #ff00ff;">256</span>,pastel,gree);</p>
<p style="text-align: left;">}</p>
</blockquote>
<blockquote>
<p style="text-align: left;"><span style="color: #339966;">void</span> DrawLine(<span style="color: #339966;">int</span> x1, <span style="color: #339966;">int</span> y1, <span style="color: #339966;">int</span> x2, <span style="color: #339966;">int</span> y2,colorRGBA cor1,colorRGBA cor2){</p>
<p style="text-align: left;"><strong>...</strong></p>
<p style="text-align: left;"><strong>tamanho_atual++;                                                                                                                               cor = interpolar(cor1,cor2, tamanho_atual/tamanho_final);</strong>
<strong>PutPixel(xp,yp,cor);</strong></p>
<p style="text-align: left;"><strong>...</strong></p>
<p style="text-align: left;">}</p>
</blockquote>
<img class="alignnone size-full wp-image-66 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-114450.png" alt="screenshot-from-2017-02-23-114450" width="512" height="540" />
<p style="text-align: center;">Figura 13 - DrawLine com interpolação de Cor.</p>
<p style="text-align: justify;"><strong>Triângulos</strong></p>
<p style="text-align: justify;">Agora de forma trivial, vamos desenhar um triângulo na tela, para isso, basta informar as suas arestas e juntamente com a Função DrawLine temos um triângulo desenhado na tela, como podemos observar na <strong>Figura 15</strong>.</p>
<p style="text-align: justify;">O algoritmo é simples, a função DrawTriangle recebe seus vértices e e passa função DrawLine, cuja desenha as três linhas.</p>

<div class="separator"><img class="alignnone size-full wp-image-70 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-131326.png" alt="screenshot-from-2017-02-23-131326" width="964" height="115" /></div>
<p style="text-align: center;">Figura 14 - DrawTriangle com interpolação de Cor.</p>

<blockquote>
<p style="text-align: left;"><span style="color: #339966;">void</span> MyGlDraw(<span style="color: #339966;">void)</span> {
DrawTriangle(<span style="color: #ff00ff;">128</span>,<span style="color: #ff00ff;">128</span>,<span style="color: #ff00ff;">384</span>,<span style="color: #ff00ff;">384</span>,<span style="color: #ff00ff;">128</span>,<span style="color: #ff00ff;">384</span>,red,blue,gree);
DrawTriangle(<span style="color: #ff00ff;">160</span>,<span style="color: #ff00ff;">128</span>,<span style="color: #ff00ff;">384</span>,<span style="color: #ff00ff;">352</span>,<span style="color: #ff00ff;">384</span>,<span style="color: #ff00ff;">128</span>,red,blue,gree);
DrawTriangle(<span style="color: #ff00ff;">200</span>,<span style="color: #ff00ff;">100</span>,<span style="color: #ff00ff;">300</span>,<span style="color: #ff00ff;">100</span>,<span style="color: #ff00ff;">250</span>,<span style="color: #ff00ff;">50</span>,red,blue,gree);</p>
<p style="text-align: left;">}</p>
</blockquote>
<img class="alignnone size-full wp-image-71 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-130722.png" alt="screenshot-from-2017-02-23-130722" width="512" height="540" />
<p style="text-align: center;">Figura 15 - Desenhando triângulos.</p>
<p style="text-align: justify;"><strong>Desenhando uma curva com Interpolação de Cor
</strong></p>

<div dir="ltr">O  cálculo dos dessa circunferência é utilizando diretamente no calculo de círculos,  é necessário encontrar um algoritmo, que, à semelhança do que se fez para a reta, mas tente minimizar as operações e calcule o raio da circunferência. É claro, deve utilizar a natureza simétrica, usamos o um algoritmo para o ponto de decisão:</div>
<blockquote>
<div dir="ltr"><span style="color: #339966;">void</span> drawCurve(<span style="color: #339966;">int</span> radius) {</div>
<div dir="ltr">...</div>
<div dir="ltr">if(d < <span style="color: #ff00ff;">0</span>) {                                                                                                                                                        <span style="color: #0000ff;">// escolher E    </span>                                                                                                                                               d += <span style="color: #ff00ff;">2</span> * x + <span style="color: #ff00ff;">3</span>;                                                                                                                                                 } else {                                                                                                                                             <span style="color: #0000ff;">//Escolhe NE  </span>                                                                                                                                               d += <span style="color: #ff00ff;">2</span> * (x-y) + <span style="color: #ff00ff;">5</span>;                                                                                                                                              --y;</div>
<div dir="ltr">}</div>
<div dir="ltr">...</div>
<div dir="ltr">}</div></blockquote>
<div dir="ltr">Com isso, obtemos o seguinte resultado com relação ao framwork utilizado,<strong> Figura 16</strong>:</div>
<div dir="ltr"><img class="alignnone size-full wp-image-74 aligncenter" src="https://barreirocg.files.wordpress.com/2017/02/screenshot-from-2017-02-23-152711.png" alt="screenshot-from-2017-02-23-152711" width="512" height="540" /></div>
<div dir="ltr" style="text-align: center;">Figura 16- drawCurve.</div>
<p style="text-align: justify;"><strong>Resultados e Discussão</strong></p>
<p style="text-align: justify;">A rasterização de pontos proporciona uma infinidade de possíbilidades em computação gráfica, Um algoritmo de traçado de  retas, o Bresenham é de grande utilidade e eficiência.</p>
<p style="text-align: justify;">Principais dificuldades foi na implementação do algoritmo de Bresenham e interpolação de cor, a principal dificuldade com Bresenham foi com relação aos oito octantes, depois de muita pesquisa e leitura, foi possível escrever um algoritmo valido para todos os octantes.</p>
<p style="text-align: justify;">Com relação a interpolação de cor. Seguindo o Foley, e as informações sobre interpolação Linear, apresentava alguns erros e simplesmente não funcionava, visto que o calculo final sempre resultava em 0.00001, então foi feito mudado todo o algoritmo, e apenas adicionando uma interpolação incremental com relação ao tamanho da reta e o tamanho atual da reta.</p>
<p style="text-align: justify;"><strong style="text-align: justify;">Considerações Finais</strong></p>
<p style="text-align: justify;">A rasterização de pontos é muito interessante e ambre porta para intendimentos de modelagem e cálculos para desenho gráficos, podemos, por exemplo, utilizar uma ferramenta gráfica para desenhar, exportar pontos e criar uma desenho, utilizando a rasterização de pontos, de fato, existe diversas ferramentas para isso, mas o ideal é entender como funciona.</p>
<p style="text-align: justify;"><strong>Referências</strong></p>

<ol style="text-align: justify;">
	<li>Anotações de Aula do Prof. Christian Azambuja Pagot (2016.2)</li>
	<li>Slides de Disciplina CG 2016.2 Disponibilizado no SIGAA UFPB (2016.2)</li>
	<li>http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/ (02/2017)</li>
	<li>http://www.demic.fee.unicamp.br/~jeff/ArquivosIndex/Bresenham (02/2017)</li>
</ol>
 
