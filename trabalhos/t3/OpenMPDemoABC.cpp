#include <algorithm>
#include <iostream>
#include <string>
#include <omp.h>
#include <vector>

using namespace std;

class Vetor_Comp {
private:
  char* array;
  int index;
  int size;
  int nTimes;
public:
  Vetor_Comp(int tam){
    size = tam;
    array = new char[size];
  }
  void Add_char(char c, int i){

    array[i] = c;

  }
  int Countchar(char c){
    return count(array, array+size, c);
  }
  void FillVector(){
      std::fill(array, array + size, '-');
  }
  void PrintVector(){
    for(int i = 0; i < size; i++){
      cout << array[i] << ' ';
    }
    cout << endl;
  }
};

class OpenMP_Funcions {
private:
  int nThreads;
  int Tam;
  int chuncksize;
  Vetor_Comp* array;
public:
  OpenMP_Funcions(int threads, int nT){
    nThreads = threads;
    Tam = nT;
    chuncksize = Tam/nThreads;
    array = new Vetor_Comp(Tam);
    array->FillVector();
  }
  void print(){
    int tmp;
    char temp;
    array->PrintVector();
    for(int i = 0; i < nThreads; i++){
      temp = 'A'+i;
      tmp = array->Countchar(temp);
      cout << temp << ": " << tmp << " ";
    }
    cout << endl << endl;

  }
  void static_with_chunk(){
    #pragma omp parallel for shared(array) schedule(static, chuncksize)
      for(int i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }
  }
  void static_without_chunk(){
    #pragma omp parallel for shared(array) schedule(static)
      for(int i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }

  }
  void dynamic_with_chunk(){
    #pragma omp parallel for shared(array) schedule(dynamic, chuncksize)
      for(int i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }

  }
  void dynamic_without_chunk(){
    #pragma omp parallel for shared(array) schedule(dynamic)
      for(int i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }
  }
  void guided_with_chunk(){
    #pragma omp parallel for shared(array) schedule(guided, chuncksize)
      for(int i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }
  }
  void guided_without_chunk(){
    #pragma omp parallel for shared(array) schedule(guided)
      for(int i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }
  }
  void sch_runtime(){
    #pragma omp parallel for shared(array) schedule(runtime)
      for(int i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }

  }
  void sch_auto(){
    #pragma omp parallel for shared(array) schedule(auto)
      for(int i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }
  }
  void no_exclusion(){
    int i;
    #pragma omp parallel
      for(i = 0; i < Tam; i++){
        array->Add_char('A' + omp_get_thread_num(), i);
      }
  }
};

void exec_all(OpenMP_Funcions func){
  cout << "Schedule (static) with Chunk" << endl;
  func.static_with_chunk();
  func.print();
  cout << "Schedule (static) without Chunk" << endl;
  func.static_without_chunk();
  func.print();
  cout << "Schedule (dynamic) with Chunk" << endl;
  func.dynamic_without_chunk();
  func.print();
  cout << "Schedule (dynamic) without Chunk" << endl;
  func.dynamic_without_chunk();
  func.print();
  cout << "Schedule (guided) with Chunk" << endl;
  func.guided_with_chunk();
  func.print();
  cout << "Schedule (guided) without Chunk" << endl;
  func.guided_without_chunk();
  func.print();
  cout << "Schedule (runtime)" << endl;
  func.sch_runtime();
  func.print();
  cout << "Schedule (auto)" << endl;
  func.sch_auto();
  func.print();
  cout << "No exclusion" << endl;
  func.no_exclusion();
  func.print();


}

int main() {
  int n_threads;
  int occur;

  cout << "Digite o número de Threads: ";
  cin >> n_threads;

  cout << "Digite o Tamanho do Vetor: ";
  cin >> occur;

  omp_set_num_threads(n_threads); //seta o numero de threads de acordo com o argumento

  OpenMP_Funcions funcs(n_threads, occur);
  exec_all(funcs);


  return 0;
}
