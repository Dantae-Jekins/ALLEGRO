### Objetivo

O objetivo era a criação de um jogo com um fator educacional, sendo construído totalmente em C ou CPP sem o uso de "engines" e apenas com o uso da API ALLEGRO. 
(O Objetivo foi concluído obviamente)

Alguns conceitos foram utilizados amplamente, estes sendo:

- Renderização com o ALLEGRO
- Virtualização de objetos
- Movimentação de objetos
- Colisões entre objetos
- Leitura de arquivos

Além de conceitos genéricos como Estruturas, ponteiros, alocação de memória e as demais ferramentas de C.
É importante mencionar que este código não compila na IDE da microsoft (Visual Studio), o compilador principal usado foi o GCC version 11.2.0 (Debian 11.2.0-13)

O código fonte se encontra em src/ e suas nomeclaturas condizem exatamente com a sua função.


# IMPORTANTE

**Como mencionado o jogo é compilável, mas um bug (que eu tenho ideia do que é) presente apenas no sistema windows e possívelmente no mac impede que o jogo rode, por isso o único ambiente de testes adequado até agora é o Debian 11.2.0-13 (wsl não funciona dada a falta de interface gráfica) com kde plasma. E já que era apenas um projeto de faculdade também não vou me dar o trabalho de resolver**
