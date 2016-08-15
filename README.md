# Simulador de processos


> Trabalho realizado para matéria MAC0422 - Sistemas Operacionais, IME USP

O simulador de processos deve receber como entrada um arquivo de trace, em texto puro, que possui varias linhas como a seguinte: 
```
t0 nome dt deadline
```
`t0` e o instante de tempo em segundos que o processo chega no sistema, `nome` e uma string sem espaços em branco que identifica o processo, `dt` e o quanto de tempo **real** da CPU deve ser simulado para aquele processo e `deadline` e o instante de tempo antes do qual aquele processo precisa terrminar. `t0`, `dt` e `deadline` sao numeros reais.

Cada linha do arquivo de entrada representa portanto um processo, que devera ser simulado no simulador como uma unica thread. Cada thread precisa ser um loop que realize qual quer operação que consuma tempo real da CPU. Nao há uma predefinição de qual deve ser essa operação.

Assim, se o simulador receber como entrada um arquivo que contenha apenas a linha:
```
1 processo0 10 11
```

e de se esperar, num cenario ideal, que no instante de tempo 1 segundo uma thread seja criada para representar o `processo0` e que no instante de tempo 11 segundos o `processo0` termine de executar.

O simulador deve finalizar sua execução assim que todos os processos terminarem de ser simulados.

O simulador sera mais interessante de ser executado com traces que permitam  mais de um processo ao mesmo tempo competindo pela CPU (ou pelas CPUs em casos onde o computador tenha mais de 1 unidade de processamento). Nessas situações o escalonador de processos implementado no simulador tera um papel fundamental e provavelmente levar a a diferentes resultados.

Diversos escalonadores de processos existem. Neste EP o simulador deve implementar os seguintes escalonadores:

1. First-Come First-Served
2. Shortest Remaining Time Next
3. Escalonamento com multiplas filas 


A invocação do simulador no [ep1sh] deve receber como primeiro parametro obrigatório o número representando cada escalonador, conforme a listagem acima, como segundo parametro obrigatorio o nome do arquivo de trace e como terceiro parametro obrigat ˆ orio o nome de um arquivo que ser a criado pelo simulador com 1 linha para cada processo e mais 1 linha extra no final. Cada linha por processo
devera ter o seguinte formato: 

```
nome tf tr
```
Onde `nome` e o identificador do processo, `tf` e o instante de tempo quando o processo terminou sua execução e `tr` e o tempo "**de relogio**" que o processo levou para executar, ou seja,  `tf-t0`.

A linha extra deve conter um unico numero que informara a quantidade de mudanças de contexto que ocorreram durante a simulação. Ou seja, a quantidade de vezes que as CPUs deixaram de rodar um processo para rodar outro.

O simulador deve receber ainda como quarto parametro opcional, o caracter `d`. Quando esse parametro for usado, o simulador devera exibir os seguintes eventos, assim que eles acontecerem, na saída de erro (*stderr*):

- chegada de um processo no sistema, informando a linha do trace daquele processo
- uso da CPU por um processo, informando qual o processo que comec¸ou a usar a CPU e qual CPU ele esta usando 
- liberação da CPU por um processo, informando qual o processo que deixo ˜ u de usar a CPU e qual CPU ele esta liberando
- finalizac¸ao da execução do processo, informando a linha que ser a escrita no arquivo de saída
- quantidade de mudanças de contexto 

O formato de exibição dessas informações é livre.
