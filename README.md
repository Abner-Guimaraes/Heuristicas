# Heurísticas: Implementação de Algoritmos de Otimização em C#

Este repositório contém a implementação de duas heurísticas populares para resolver problemas de otimização NP-Difícil em C#. Os algoritmos desenvolvidos são destinados a resolver um problema específico escolhido entre aqueles abordados no Trabalho Prático 1.

# Objetivo
O objetivo deste trabalho é implementar e comparar duas abordagens heurísticas: uma baseada em Busca Local e outra em Processo Evolutivo. Ambas as técnicas são aplicadas ao mesmo problema, permitindo uma comparação direta de sua eficácia e desempenho.

# Problema Escolhido
O problema escolhido para este trabalho é o clássico Problema do Caixeiro Viajante (TSP). O TSP é um problema de otimização combinatória que consiste em encontrar o caminho mais curto que visita cada cidade exatamente uma vez e retorna à cidade de origem.

# Heurísticas Implementadas
1. Busca Local
A heurística de Busca Local é um método iterativo que examina soluções vizinhas à solução atual em busca de melhorias. Neste contexto, a Busca Local será aplicada ao TSP com o objetivo de melhorar progressivamente a rota do caixeiro viajante.

2. Processo Evolutivo
O Processo Evolutivo é uma técnica baseada em algoritmos genéticos, inspirada no processo de seleção natural. Neste trabalho, aplicaremos um algoritmo genético ao TSP, criando uma população inicial de soluções e aplicando operadores genéticos como mutação e recombinação para evoluir soluções cada vez melhores.