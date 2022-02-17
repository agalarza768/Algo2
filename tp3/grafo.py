class Grafo:
	def __init__(self, es_dirigido):
		self.es_dirigido = es_dirigido
		self.grafo = {}

	def agregar_vertice(self, v):
		self.grafo[v] = {}

	def borrar_vertice(self, v):
		self.grafo.pop(v)
		for w in self.grafo.keys():
			if v in self.grafo[w].keys():
				self.grafo[w].pop(v)

	def agregar_arista(self, v, w, peso):
		self.grafo[v][w] = peso
		if not self.es_dirigido:
			self.grafo[w][v] = peso

	def borrar_arista(self, v, w):
		if not self.es_dirigido:
			self.grafo[w].pop(v)
		self.grafo[v].pop(w)

	def estan_unidos(self, v, w):
		return w in self.grafo[v]
		
	def peso_arista(self, v, w):
		return self.grafo[v][w]

	def obtener_vertices(self):
		return list(self.grafo.keys())
        
	def adyacentes(self, v):
		return list(self.grafo[v].keys())
        
	def __len__(self):
		return len(self.grafo)
