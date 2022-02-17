#!/usr/bin/python3
import sys
from grafo import Grafo
import csv
from comandos import camino_mas_corto, todas_en_rango, canciones_mas_importantes, ciclo, clustering, recomendacion

GRAFO_CANCIONES = 0
LISTA_MAS_IMPORTANTES = 1

COMANDO = 0
PARAMETROS = 1

def procesar_comando(linea_comandos, grafo_completo, usuarios, canciones, datos_a_actualizar):
	grafo_canciones, list_mas_importantes = datos_a_actualizar
	if linea_comandos[COMANDO] == 'camino':
		if len(linea_comandos) < 2: return
		parametros = linea_comandos[PARAMETROS].split(' >>>> ')
		if len(parametros) < 2: return
		origen, destino = parametros
		
		if origen not in canciones or destino not in canciones:
			print('Tanto el origen como el destino deben ser canciones')
			return
		camino_mas_corto(grafo_completo, origen, destino)

	elif linea_comandos[COMANDO] == 'mas_importantes':
		cant_canciones = int(linea_comandos[PARAMETROS])
		if len(linea_comandos) < 2: return
		datos_a_actualizar[LISTA_MAS_IMPORTANTES] = canciones_mas_importantes(grafo_completo, cant_canciones, canciones, list_mas_importantes)
		return

	elif linea_comandos[COMANDO] == 'recomendacion':
		if len(linea_comandos) < 2: return
			
		parametros = linea_comandos[PARAMETROS].split(' ', 2)
		if len(parametros) < 3: return
			
		opcion_recomendacion, n, canciones_favoritas = parametros
		lista_canciones = canciones_favoritas.split(' >>>> ')
		recomendacion(grafo_completo, opcion_recomendacion, n, lista_canciones, canciones)

	elif linea_comandos[COMANDO] == 'ciclo':
		if len(linea_comandos) < 2: return
			
		parametros = linea_comandos[PARAMETROS].split(' ', 1)
		if len(parametros) < 2: return
			
		n, cancion = parametros
		
		if cancion not in canciones: return
		
		if not grafo_canciones:
			grafo_canciones = Grafo(False)
			crear_grafo_canciones(grafo_canciones, canciones)
			datos_a_actualizar[GRAFO_CANCIONES] = grafo_canciones
		ciclo(grafo_canciones, n, cancion)

	elif linea_comandos[COMANDO] == 'rango':
		if len(linea_comandos) < 2: return
			
		parametros = linea_comandos[PARAMETROS].split(' ', 1)
		if len(parametros) < 2: return
			
		n, cancion = parametros
		
		if cancion not in canciones: return
		
		if not grafo_canciones:
			grafo_canciones = Grafo(False)
			crear_grafo_canciones(grafo_canciones, canciones)
			datos_a_actualizar[GRAFO_CANCIONES] = grafo_canciones

		todas_en_rango(grafo_canciones, n, cancion)
		return

	elif linea_comandos[COMANDO] == 'clustering':
		if len(linea_comandos) < 2:
			cancion = ""
		else:
			cancion = linea_comandos[PARAMETROS]
		if not grafo_canciones:
			grafo_canciones = Grafo(False)
			crear_grafo_canciones(grafo_canciones, canciones)
			datos_a_actualizar[GRAFO_CANCIONES] = grafo_canciones
		cant_adyacentes = {}
		for v in grafo_canciones.obtener_vertices(): cant_adyacentes[v] = len(grafo_canciones.adyacentes(v))
		clustering(grafo_canciones, cancion, cant_adyacentes)
		return

	else:
		return

def procesar_entrada(grafo_completo, usuarios, canciones, datos_a_actualizar):
	for linea in sys.stdin:
		linea = linea.rstrip('\n')
		linea_sep = linea.split(' ', 1)
		
		if linea_sep[0] == '':
			break
			
		procesar_comando(linea_sep, grafo_completo, usuarios, canciones, datos_a_actualizar)

def csv_crear_grafo(grafo, ruta_archivo, canciones, usuarios):
	with open(ruta_archivo, "r") as archivo:
		next(archivo)
		for linea in archivo:
			linea = linea.rstrip('\n')
			contenido = linea.split('\t')

			_, user_id, track_name, artist, _, playlist_name, _ = contenido

			track = " - ".join((track_name, artist))
			
			if user_id not in usuarios:
				grafo.agregar_vertice(user_id)
				usuarios.add(user_id)
			if track not in canciones:
				grafo.agregar_vertice(track)
				canciones[track] = []

			playlist_cancion = canciones.get(track, None)
			playlist_cancion.append(playlist_name)
			canciones[track] = playlist_cancion
			grafo.agregar_arista(user_id, track, playlist_name)

def crear_grafo_canciones(grafo, canciones):
	playlist_canciones = {}		

	for cancion in canciones.keys():
		grafo.agregar_vertice(cancion)
		for playlist in canciones[cancion]:
			lista_canciones = playlist_canciones.get(playlist, [])
			lista_canciones.append(cancion)
			playlist_canciones[playlist] = lista_canciones
	
	for playlist, tracks in playlist_canciones.items():
		for i in range(len(tracks)):
			j = i + 1
			while j < len(tracks):
				grafo.agregar_arista(tracks[i], tracks[j], playlist)
				j += 1

def main():
	if len(sys.argv) < 2:
		print("ERROR")
		return
	
	grafo_completo = Grafo(False)
	grafo_canciones = None
	list_mas_importantes = None

	canciones = {}
	usuarios = set()
	
	datos_a_actualizar = [grafo_canciones, list_mas_importantes]

	csv_crear_grafo(grafo_completo, sys.argv[1], canciones, usuarios)
	procesar_entrada(grafo_completo, usuarios, canciones, datos_a_actualizar)

main()
