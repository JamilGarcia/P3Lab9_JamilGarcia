#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void lectura();
void EvaluarString();
void CrearClase_h(vector<string>);
void CrearClase_cpp(vector<string>);
void Escribir(string, string);
string CadenaTexto = "";

int main()
{
    lectura();
    //cout << CadenaTexto << endl;
    EvaluarString();
    return 0;
}

void EvaluarString()
{
    vector<string> listaAtri;
    for (int i = 0; i < CadenaTexto.length(); i++)
    {
        if (CadenaTexto[i] == '[')
        {
            listaAtri.clear();
            vector<string> listaAtri;
        }
        else if (CadenaTexto[i] == ']')
        {
            CrearClase_h(listaAtri);
            CrearClase_cpp(listaAtri);
            listaAtri.clear();
            vector<string> listaAtri;
        }
        else if (CadenaTexto[i] == ':')
        {
            //cout << "Entra3" << endl;
            string strTemp = "";
            i++;
            for (int j = i; j < CadenaTexto.length(); j++)
            {
                //cout << "CadenaT: " << CadenaTexto[j];
                //if (!((int) CadenaTexto[j] > 64 && (int) CadenaTexto[j] < 91) || !(((int) CadenaTexto[j] > 96 && (int) CadenaTexto[j] < 123)) ){
                if (CadenaTexto[j] == ' ' || CadenaTexto[j] == '\t')
                {
                    //cout << " 2 " << strTemp << endl;
                    strTemp += " "; 
                    listaAtri.push_back(strTemp);
                    strTemp = "";
                    break;
                }
                else if (CadenaTexto[j] == ']' || CadenaTexto[j] == '[')
                {
                }
                else
                {
                    //cout << " StrTemp: " << strTemp<< endl;
                    strTemp += CadenaTexto[j];
                }
            }
        }
    }
}

void CrearClase_h(vector<string> listaAtri)
{
    //cout << "Entra" << endl;  
    string nombreClase = listaAtri[0];
    int contTemp = 0; //0 Significa que va para TipoVariable, 1 va para Atributo
    string StringCompleto;
    vector<string> TipoVariable, Atributo;
    int contAtri;

    for (int i = 1; i < listaAtri.size(); i++)
    {
        //cout << "Entra 6" << endl;
        string temporal = listaAtri[i];
        string temporal2 = "";
        for (int j = 0; j < temporal.length(); j++)
        {
            //cout << "temporal: " << temporal[j] << endl;
            if (temporal[j] == '|' || temporal[j] == ' ')
            {
                //cout << "Entraaa" << endl;

                if (contTemp == 0)
                {
                    //cout << temporal2 << endl;
                    TipoVariable.push_back(temporal2);
                    temporal2 = "";
                    contTemp = 1;
                }
                else
                {
                    //cout << " temporal2 " << temporal2 << endl;
                    Atributo.push_back(temporal2);
                    temporal2 = "";
                    contTemp = 0;
                }
            }
            else
            {
                temporal2 += temporal[j];
            }
        }
    }

    //cout << TipoVariable.size();

    contAtri = 0;

    StringCompleto = "#ifndef " + nombreClase + "_H\n" + "#define " + nombreClase + "_H\n" + "\n" + "include <string>\n" + "\n" + "using namespace std;\n" + "\n" + "class " + nombreClase + "{\n" + "     private:\n";

    while (contAtri < TipoVariable.size())
    {
        StringCompleto += "         " + TipoVariable[contAtri] + " " + Atributo[contAtri] + "\n";
        contAtri++;
    }
    contAtri = 0;

    StringCompleto += "     public:\n";
    StringCompleto += "         " + nombreClase + "();\n" + "         " + nombreClase + "(";
    while (contAtri < TipoVariable.size())
    {
        if (contAtri + 1 == TipoVariable.size())
        {
            StringCompleto += TipoVariable[contAtri] + ");\n";
            contAtri++;
        } else {
        StringCompleto += TipoVariable[contAtri] + ",";
        contAtri++;
        }
    }

    contAtri = 0;

    while (contAtri < TipoVariable.size())
    {
        StringCompleto += "         void_" + Atributo[contAtri] + "(" + TipoVariable[contAtri] + ");\n";
        contAtri++;
    }
    contAtri = 0;

    while (contAtri < TipoVariable.size())
    {
        StringCompleto += "         " + TipoVariable[contAtri] + "get_" + Atributo[contAtri] + "();\n";
        contAtri++;
    }
    contAtri = 0;

    StringCompleto += "         string toString()\n";
    StringCompleto += "         ~" + nombreClase + "();\n" + "};\n" + "\n" + "#endif";

    string nombre = nombreClase + ".txt";
    //cout << StringCompleto;
    Escribir(nombre, StringCompleto);
}

void CrearClase_cpp(vector<string> listaAtri)
{
    
    string nombreClase = listaAtri[0];
    int contTemp = 0; //0 Significa que va para TipoVariable, 1 va para Atributo
    string StringCompleto;
    vector<string> TipoVariable, Atributo;
    int contAtri;

    for (int i = 1; i < listaAtri.size(); i++)
    {
        //cout << "Entra 6" << endl;
        string temporal = listaAtri[i];
        string temporal2 = "";
        for (int j = 0; j < temporal.length(); j++)
        {
            //cout << "temporal: " << temporal[j] << endl;
            if (temporal[j] == '|' || temporal[j] == ' ')
            {
                //cout << "Entraaa" << endl;

                if (contTemp == 0)
                {
                    //cout << temporal2 << endl;
                    TipoVariable.push_back(temporal2);
                    temporal2 = "";
                    contTemp = 1;
                }
                else
                {
                    //cout << " temporal2 " << temporal2 << endl;
                    Atributo.push_back(temporal2);
                    temporal2 = "";
                    contTemp = 0;
                }
            }
            else
            {
                temporal2 += temporal[j];
            }
        }
    }

    //cout << TipoVariable.size();

    contAtri = 0;
    
    StringCompleto = "#include ";
    StringCompleto +=  "\" "+ nombreClase + ".h\"\n"
                    + "\n"
                    + nombreClase + "::" + nombreClase + "(){\n"
                    + "}\n"
                    + "\n"
                    + nombreClase + "::" + nombreClase + "(";

    while(contAtri < TipoVariable.size()){
        if(contAtri + 1 == TipoVariable.size()){
            StringCompleto += TipoVariable[contAtri] + "_" + Atributo[contAtri]+ "){\n"; 
            contAtri++;
        }else {
            StringCompleto += TipoVariable[contAtri] + "_" + Atributo[contAtri]+ ", "; 
            contAtri++;
        }
        
    }
    
    contAtri = 0;

    while (contAtri < TipoVariable.size()){
        StringCompleto += "     " + Atributo[contAtri] + " =  _" + Atributo[contAtri] + ";\n";
        contAtri++;  
    }
    contAtri = 0;

    while(contAtri < TipoVariable.size()){
        StringCompleto += "void" + nombreClase + "::set_" + Atributo[contAtri] + "(" + TipoVariable[contAtri] + "_" + Atributo[contAtri] + "){\n"
                        + "     " + Atributo[contAtri] + " =  _" + Atributo[contAtri] + ";\n"
                        + "}\n";
        contAtri++;
    }
    contAtri = 0;


    while(contAtri < TipoVariable.size()){
            //cout << "Entra2 " << endl; 
        StringCompleto += TipoVariable[contAtri] + " " + nombreClase + "::get_" + Atributo[contAtri] + "(){\n" 
                        + "     return " + Atributo[contAtri] + "\n"
                        + "}\n"; 
        contAtri++;
    }
    contAtri = 0;

    StringCompleto += "string " + nombreClase + "::toString(){\n"
                        + "return " + "\"" + nombreClase + "-> " + Atributo[contAtri] + ": \" "; 

    
    while(contAtri < TipoVariable.size()){
        if (TipoVariable[contAtri] == "string"){
            StringCompleto += "+" + Atributo[contAtri];
          } else {
              StringCompleto += "+";
              StringCompleto += "\" |" + Atributo[contAtri] + ": \" " + "+to_string(" + Atributo[contAtri] + ")" ;
          }

        contAtri++; 
    }
    contAtri = 0;
    

    StringCompleto += nombreClase + "::~" + nombreClase + "(){\n}\n"; 
    //cout << StringCompleto; 
    string nombre = nombreClase + ".txt";
    Escribir(nombre, StringCompleto);
}

void Escribir(string nombre, string cadena)
{
    ofstream archivo;
    archivo.open(nombre.c_str(), ios::out);

    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    archivo<<cadena; 
    archivo.close();
}
void lectura()
{
    //cout << "entra2";
    ifstream archivoLeer;
    string texto;

    archivoLeer.open("generator.txt", ios::in);

    if (archivoLeer.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }

    while (!archivoLeer.eof())
    {
        getline(archivoLeer, texto);
        CadenaTexto += texto;
    }

    archivoLeer.close();
}
