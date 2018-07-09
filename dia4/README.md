# Editorial

## Problema A: Pair Of Lines
Se o número de pontos for menor que 3, sempre podemos traçar uma linha contendo todos. Senão, vamos pegar 3 pontos quaisquer.
Se houver uma resposta, há 2 cenários possíveis:
  * Uma linha passa por 2 deles e a outra passa pelo outro
  * As duas linhas passam pelos 3 pontos
  
Como só queremos saber se existe ou não uma resposta, podemos para cada par dentre os 3 pontos fixados, verificar se é possível
separar todos os pontos em 2 conjuntos:
  * Os contidos na linha que passa pelo par
  * Os não contidos na linha que passa pelo par
  
E então verificar se os pontos pontos não contidos na linha que passa pelo par são colineares.
Para verificar se 3 pontos (vamos chamar de p1, p2 e p3) são colineares, basta checar se o cross product entre os vetores
p2-p1 e p3-p1 é igual a 0. Para verificar se *n* pontos são colineares, podemos fixar um deles como origem, e então comparar
um dos vetores formado entre outro ponto e essa origem com todos os outros vetores formados entre algum ponto e essa origem.

## Problema B: Nearest Vectors
Como os vetores tem início no mesmo ponto (origem), podemos afirmar que se ordenarmos eles por ângulo, o par de pontos mais
próximo estará em posições consecutivas ou na primeira e na última posição. Para ordenar os pontos por ângulo podemos usar
a função atan2(y, x) (referência completa em: http://www.cplusplus.com/reference/cmath/atan2/).
Só é preciso tomar cuidado na hora de calcular o ângulo entre 2 vetores porque essa função retorna valores no intervalo [-pi,pi], mas basta lembrar
que para ter o equivalente positivo de um ângulo negativo só precisamos somar 2*pi nele. Como o output deve ser as posições
originais dos vetores mais próximos no input, para cada vetor precisamos guardar seu índice original antes da ordenação.
Podemos fazer isso com um pair, por exemplo.

## Problema C: Rectangle and Square
Como só há 8 pontos, podemos testar todas as permutações desses pontos, separando metade dos pontos para formar
o quadrado e metade para formar o retângulo. Podemos gerar as permutações com a função next_permutation 
(http://www.cplusplus.com/reference/algorithm/next_permutation/). Para testar se 4 pontos formam um retângulo,
basta checar se seus 4 ângulos são retos, que é quando dot product entre os pares de vetores correspondentes aos lados
consecutivos são iguais a 0. Para verificar se 4 pontos formam um quadrado só precisamos adicionar a verificação de que
os tamanhos dos 4 lados devem ser iguais.

## Problema D: Two Squares
Como um dos quadrados tem seus lados paralelos aos eixos e o outro está rotacionado 45º, podemos afirmar que para que haja
intersecção ou que um esteja contido no outro, basta uma das condições:
  * Um dos vértices de um está contido no outro
  * O centro de um está contido no outro
 
Como o número de lados do quadrado é apenas 4, podemos verificar se o cross product entre os vetores formados entre um
vértice e o ponto (que estamos testando se está dentro do quadrado) e o vértice e o próximo vértice adjacente dão sempre
maiores ou iguais a zero ou menores ou iguais a zero (nesse caso incluimos o zero pois se o ponto estiver no lado do quadrado
é considerado que está dentro).

## Problema E: Polygons
Nesse problema, basta juntar todos pontos num único vetor, guardando para cada ponto qual o polígono a que originalmente pertence,
e então fazer o convex hull do conjunto de todos os pontos. Se o polígono B está estritamente contido no polígono A, todos
os pontos do convex hull perteciam originalmente ao polígono A.

## Problema F: Wall
É possível ver que a parede será construída à distância *L* do convex hull de todos os pontos. Podemos separar o muro em 2 partes:
  * Paredes retas paralelas aos lados do convex hull
  * Paredes curvas entre duas paredes retas

As paredes retas terão exatamente o mesmo tamanho dos lados do convex hull. Já para as paredes curvas, podemos afirmar que
se juntarmos todas teremos um círculo completo (para enxergar isso melhor podemos ignorar as paredes retas e juntar as paredes
curvas adjacentes). Portanto, a resposta será a soma dos tamanhos das arestas do convex hull mais o perímetro do círculo formado
pelas paredes curvas. Detalhe: para arredondar o valor da saída para o inteiro mais próximo, basta usar *printf* com a máscara *%.0lf*.