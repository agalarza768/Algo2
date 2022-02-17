from grafo import Grafo
import funciones_tp3
import heapq

ITERACIONES_PAGERANK = 25
LONGITUD_CAMINO_RECOMENDACION = 10

def camino_mas_corto(grafo, origen, destino):
    camino, _ = funciones_tp3.bfs(grafo, origen, destino,None)
    if not camino:
        print("No se encontro recorrido")
        return

    cancion = camino.pop(0)
    while cancion != destino:
        usuario = camino.pop(0)
        print(f"{cancion} --> aparece en playlist --> {grafo.peso_arista(cancion, usuario)} --> de --> {usuario} -->", end = ' ')
        cancion = camino.pop(0)
        print(f"tiene una playlist --> {grafo.peso_arista(cancion, usuario)} --> donde aparece -->", end = ' ')

    print(cancion)

def todas_en_rango(grafo, n, cancion):
    _, cant = funciones_tp3.bfs(grafo, cancion, None, int(n))
    print(cant)

def canciones_mas_importantes(grafo, cant_canciones, dict_canciones, list_mas_importantes):
    if not list_mas_importantes:
        list_mas_importantes = funciones_tp3.pagerank(grafo, dict_canciones)
    n_canciones_mas_importantes = heapq.nlargest(cant_canciones, list_mas_importantes, key = lambda campo:campo[1])
    funciones_tp3.imprimir_vertices(n_canciones_mas_importantes, '; ')
    return list_mas_importantes

def ciclo(grafo, n, cancion):
    ciclo = funciones_tp3.encontrar_ciclo(grafo, int(n), cancion)
    if ciclo is not None:
        salida = " --> ".join(ciclo)
        print(salida)
    else:
        print("No se encontro recorrido")

def clustering(grafo_canciones, cancion, cant_adyacentes):
    if cancion != "":
        print("%1.3f" % funciones_tp3.clustering_particular(grafo_canciones, cancion, cant_adyacentes))
    else:
        print("%1.3f" % funciones_tp3.promedio_clustering(grafo_canciones, cant_adyacentes))

def recomendacion(grafo_completo, opcion_recomendacion, n, lista_canciones, dict_canciones):
    recomendados = {}
    for cancion in lista_canciones:
        funciones_tp3.pagerank_personalizado(grafo_completo, cancion, recomendados, LONGITUD_CAMINO_RECOMENDACION)

    lista_recomendada = []
    for k, v in recomendados.items():
        if (opcion_recomendacion == "canciones" and k not in dict_canciones) or (opcion_recomendacion == "usuarios" and k in dict_canciones) or k in lista_canciones:
            continue
        lista_recomendada.append((k, v))
    lista_recomendada = heapq.nlargest(int(n), lista_recomendada, key = lambda campo:campo[1])
    funciones_tp3.imprimir_vertices(lista_recomendada, '; ')
    
    



