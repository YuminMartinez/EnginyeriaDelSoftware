#include "enemies.h"

#include "dep/inc/xml/rapidxml.hpp"
#include "dep/inc/xml/rapidxml_print.hpp"
#include "dep/inc/xml/rapidxml_utils.hpp"
#include "dep/inc/xml/rapidxml_iterators.hpp"
#include <fstream>
#include <sstream>
#include <string>




int main()
{
	
	// Create an XML document to read an XML file 

	rapidxml::xml_document <>doc; //doc será donde se almacene toda la información que leas del archivo.

	std::ifstream file("config.xml"); //Abre el archivo config.xml para lee
	
	if (!file.is_open()) {
		std::cerr << "No se pudo abrir config.xml\n";
		system("dir");
		return 0;
	}

	//Crea un buffer en memoria que actuará como un contenedor temporal para el contenido del archivo.
	std::stringstream buffer; 

	buffer << file.rdbuf();// Copia todo el contenido del archivo dentro del buffer.

	
	file.close();  


	std::string content(buffer.str()); //Convierte el buffer en un string estándar de C++.
	
	//Llama a RapidXML para parsear (analizar) el contenido del string y construir el árbol de nodos XML.

	doc.parse<0>(&content[0]); //&content[0] devuelve un puntero al primer carácter del string.
	//el parse toma el texto del XML y lo convierte en nodos en memoria, creando un árbol jerárquico que refleja la estructura del XML.




	//Acceso al archivo

	//declarar root node --> pRoot apunta al nodo <enemies>, la raíz de todos los enemigos.
	rapidxml::xml_node<>* pRoot = doc.first_node();

	//for para pasar por todos los hijos de <enemies <( es decir <enemic<) // // Primer for: recorrer todos los <enemy>
	for (rapidxml::xml_node<>* pChild = pRoot->first_node("enemic"); pChild; pChild = pChild->next_sibling())
	{
		//// Aquí pChild apunta a cada <enemic> individual por cada for 

		

		// Segundo for: recorrer todos los hijos de <enemy> (<name>, <health>, etc.)
		for (rapidxml::xml_node <>* pChildI = pChild->first_node(); pChildI; pChildI = pChildI->next_sibling())
		{
			std::cout << pChildI->name() << " -> " << pChildI->value() << std::endl;
		}
		std::cout << "--------------------" << std::endl;
		
	}

	//
	return 1;
}