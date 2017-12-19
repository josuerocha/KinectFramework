/*GERANDO COORDENADAS E CORES ALEATÓRIAS PARA POINT CLOUD

*/

///STANDARD INCLUDES
#include <iostream>

///PCL INCLUDES
#include <pcl/point_types.h>

///CUSTOM INCLUDES
#include <IO.h>

using namespace std;
using namespace pcl;

int main (int argc, char** argv){

    //pcl::PointXYZ para pontos sem cor
    //pcl::PointXYZRGBA pontos com RGB e ALPHA

    PointCloud<PointXYZRGBA> cloud; //criando nuvem de pontos simples

    // Preenchendo os dados da nuvem de pontos
    cloud.width    = 5; //largura da nuvem de pontos
    cloud.height   = 1; //altura da nuvem de pontos
    cloud.is_dense = false; //identifica que esta nuvem pode possuir pontos inválidos (NaN,Inf)
    cloud.points.resize (cloud.width * cloud.height); /*Atribui tamanho da point cloud - Observação: Ocasionará erro se
    o valor passado for diferente de cloud.width * cloud.height*/

    //Loop que atribui valores para a cloud aleatoriamente
    for (size_t i = 0; i < cloud.points.size(); i++){
        //Definindo coordenadas
        cloud.points[i].x = rand() / (RAND_MAX + 1.0f);
        cloud.points[i].y = rand() / (RAND_MAX + 1.0f);
        cloud.points[i].z = rand() / (RAND_MAX + 1.0f);

        //Definindo cores
        cloud.points[i].r = (int) (rand() / (RAND_MAX + 1.0f) * 255);
        cloud.points[i].g = (int) (rand() / (RAND_MAX + 1.0f) * 255);
        cloud.points[i].b = (int) (rand() / (RAND_MAX + 1.0f) * 255);

        cloud.points[i].a = rand() / (RAND_MAX) * 255;
    }

    IO<PointXYZRGBA> io;
    PointCloud<PXYZRGBA>::Ptr cloud_ptr(&cloud);
    io.writeToPCD("teste.pcd",cloud_ptr);
    cout << "Salvos " << cloud.points.size () << " pontos em teste.pcd" << endl;

    //Execute o pcl_viewer para ver a nuvem de pontos
    cout<<"Exibindo valores salvos na nuvem de pontos"<< endl;

    for (size_t i = 0; i < cloud.points.size(); i++){
        cout<<"Ponto " << i <<endl;

        cout<<"Coordenadas" <<endl;
        cout << " " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << endl;

        cout<<"Cores" << endl;
        cout << "    " << (int) cloud.points[i].r << " " << (int) cloud.points[i].g << " " << (int) cloud.points[i].b << " " << (int) cloud.points[i].a << endl;
        cout << endl;
    }
    return (0);
}
