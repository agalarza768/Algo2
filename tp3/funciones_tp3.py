from collections import deque
from random import randint

ITERANCIONES_PAGERANK = 25

def reconstruir_camino(grafo, padres, desde, hasta):
	camino = []
	while hasta != desde:
		camino.append(hasta)
		hasta = padres[hasta]
	camino.append(hasta)

	return camino[::-1]

def bfs(grafo, desde, hasta, n):
	visitados = set()
	orden = {}
	padre = {}
	q = deque()

	visitados.add(desde)
	orden[desde] = 0
	padre[desde] = None
	q.append(desde)
	cant = 0
	while q:
		v = q.popleft()
		if v == hasta:
			return reconstruir_camino(grafo, padre, desde, hasta), None
		for w in grafo.adyacentes(v):
			if w not in visitados:
				orden[w] = orden[v] + 1
				visitados.add(w)
				padre[w] = v
				if orden[w] == n:
					cant += 1
				q.append(w)
	return None, cant

def pagerank(grafo, filtro):
	pagerank_actual = {}
	nuevo_pagerank = {}
	cantidad_adyacentes = {}
	len_grafo = len(grafo.obtener_vertices())

	for v in grafo.obtener_vertices():
		pagerank_actual[v] = 0
		cantidad_adyacentes[v] = len(grafo.adyacentes(v))

	contador = 0
	while contador < ITERANCIONES_PAGERANK:
		for v in grafo.obtener_vertices():
			pagerank_vertice(grafo, len_grafo, v, pagerank_actual, nuevo_pagerank, cantidad_adyacentes)
		pagerank_actual = nuevo_pagerank.copy()
		contador += 1

	arreglo_numero_pagerank = []
	for k, v in pagerank_actual.items():
		if k not in filtro:
			continue
		arreglo_numero_pagerank.append((k, v))

	return arreglo_numero_pagerank

def pagerank_vertice(grafo, len_grafo, vertice, pagerank_actual, nuevo_pagerank, cant_adyacentes):
	d = 0.85
	suma_pagerank_adyacentes = 0
	for w in grafo.adyacentes(vertice):
		suma_pagerank_adyacentes += pagerank_actual[w] / cant_adyacentes[w]	
	nuevo_pagerank[vertice] = (1 - d) / len_grafo + d * suma_pagerank_adyacentes

def promedio_clustering(grafo, cant_adyacentes):
	sumatoria = 0
	h = 0
	for v in grafo.obtener_vertices():
		h += 1
		sumatoria += clustering_particular(grafo, v, cant_adyacentes)
	return sumatoria / len(grafo.obtener_vertices())

def contar_adyacentes_conectados(grafo, lista_adyacentes, len_lista_adyacentes):
	contador = 0
	for i in range(len_lista_adyacentes - 1):
		for j in range(i + 1, len_lista_adyacentes):
			if grafo.estan_unidos(lista_adyacentes[i], lista_adyacentes[j]):
				contador += 1
	return contador

def clustering_particular(grafo, vertice, cant_adyacentes):
	if cant_adyacentes[vertice] < 2: return 0
	cant_adyacentes_conectados = contar_adyacentes_conectados(grafo,grafo.adyacentes(vertice), cant_adyacentes[vertice])
	return (2 * cant_adyacentes_conectados) / (cant_adyacentes[vertice] * (cant_adyacentes[vertice] - 1))

def _encontrar_ciclo(grafo, vertice_actual, origen, n, visitados, camino):
	visitados.add(vertice_actual)
	if len(camino) == n:
		if origen in grafo.adyacentes(vertice_actual):
			camino.append(origen)
			return camino
		return None
	for w in grafo.adyacentes(vertice_actual):
		if w in visitados: continue
		solucion = _encontrar_ciclo(grafo, w, origen, n, visitados, camino + [w])	
		if solucion is not None:
			return solucion
	
	visitados.remove(vertice_actual)
	return None

def encontrar_ciclo(grafo, n, origen):
	if n < 2:
		return None, False
		
	camino = []
	visitados = set()
	camino.append(origen)
	
	return _encontrar_ciclo(grafo, origen, origen, n, visitados, camino)

def pagerank_personalizado(grafo, vertice, recomendados, longitud_camino):
	recomendados[vertice] = 1
	for i in range(longitud_camino):
		adyacentes = grafo.adyacentes(vertice)
		cant_adyacentes = len(adyacentes)
		proximo = adyacentes[randint(0, cant_adyacentes - 1)]
		recomendados[proximo] = recomendados.get(proximo, 0) + recomendados[vertice] / cant_adyacentes
		vertice = proximo

def imprimir_vertices(list_vertices, sep):
	for vertice in list_vertices:
		if vertice[0] == list_vertices[len(list_vertices)-1][0]:
			print(vertice[0])
		else:	
			print(vertice[0] , end = sep)

	
