# Itegrantes:
  - Giselly Alves Reis
  - Samuel Rios da Silva
  
# Detalhes
Implementação de inserção, consulta e remoçao de registros em arquivo binário sequencial utilizando duas funções de hashing.


# Compilação e Execução:
 Trabalho compilado com o GCC(Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0.
</br>
 Deve ser compilado o arquivo main.c: gcc main.c -o main
 </br>
 Para executar: ./main

# Uso:
 - inserir registro: deve-se inserir quatro linhas, na primeira deve conter o caractere 'i', a segunda a chave do registro (inteiro), a terceira uma sequencia de 20 caracteres indicando o nome e na quarta linha deve conter a idade.

 - consultar registro: deve-se inserir duas linhas, na primeira deve conter o caractere 'c' e, na segunda a chave do registro que se quer consultar.

 - remover registro: deve-se inserir 2 linhas, na primeira deve conter o caractere 'r' e, na segunda a chave do registro que se quer remover.

 - imprimir arquivo: deve-se inserir uma linha contendo apenas o caractere 'p'.

 - consultar media de acessos a registros do arquivo: deve-se inserir uma linha contendo apenas o caractere 'p'. Esse comando imprime duas linhas, na primeira indicando a media acessos a registros por consulta com sucesso e na segunda a media de acessos a registro por consulta sem sucesso, i.e, quando o registro procurado não se encontra no arquivo.