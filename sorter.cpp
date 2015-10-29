#include <stdio.h>      // printf, scanf, NULL 
#include <cstdlib>      // srand, rand, exit || #include <stdlib.h> 
#include <ctime>        // time || #include <time.h> 
#include <iostream>     // cout
#include <vector>       // vector
#include <fstream>      // file read
#include <algorithm>    // swap merge sort
#include <cmath>        // floor
using namespace std;

#define NUM_THREADS 10 //number of sorting functions & different threads
#define DATA_SIZE 100000 //size of data to be sorted
#define DATA_DIGITS 100000000 //length(digits) of number/s

//struct of data containing thread Id & Vector to be sorted
struct tData{
   int  tId;
   vector<int> tVector;
};
struct tData tDataArray[NUM_THREADS];//one struct per sorting method | thread

//---------------------------------------FUNCTIONS HEADERS-----------------------------------
vector<int> fileReader(string fileName);//reads a file of numbers returns a vector
void fileWriter(vector<int> &fv, string fileName);//file writer
//sorting functions  - vector is passed by address
void fileWriter(vector<int> &fv, string fileName);
void quickSort(vector <int> &x, int low, int high);
void selectionSort(vector <int> &y);
void insertionSort( vector <int> &z);
void bubbleSort(vector <int> &w);
void shellSort( vector <int> &sv);
void mergeSort(vector <int> &mv);
void heapSort(vector<int> &hv);
void bucketSort(vector<int> &bv);
void combSort(vector<int> &cv);
void cLibrarySort(vector<int> &av);
void *sorterThreadCaller(void *inData);//threads function
//------------------------------------END FUNCTIONS HEADERS----------------------------------

//---------------------------------MAIN------------------------------------------------------
int main (){

  //**************File name*************
  string fileName="unsortedNumbers.txt";
  //************************************
  
  //building file fileName^ with sample numbers for test----------------------
  srand (time(NULL));
  tDataArray[0].tId=0; // initial unsorted id

  for (int j=0; j!=DATA_SIZE;++j) tDataArray[0].tVector.push_back(rand()%DATA_DIGITS);

  fileWriter(tDataArray[0].tVector, fileName);
  //end file writting---------------------------------------------------------

  //file reading--------------------------------------------------------------
  tDataArray[0].tVector.clear();//clearing the vector for reading from file

  int temp;
  ifstream fromFile;
  fromFile.open(fileName.c_str());
    if(fromFile.fail()) {cout<<"Error, Unable to Open the file: "<<fileName<<" to read from!"<<endl;exit(1);}
  
      else while (fromFile>>temp) if (!fromFile.eof()) tDataArray[0].tVector.push_back(temp);

  fromFile.close();
  cout<<"File read: "<<fileName<<endl;
  //end file reading-----------------------------------------------------------

//multiplicating more vectors to sort in paralel-------------------------------
  for (unsigned int i=1; i<NUM_THREADS; ++i){

    tDataArray[i].tId=i;

    for (int j=0; j!=tDataArray[0].tVector.size();++j) tDataArray[i].tVector.push_back(tDataArray[0].tVector[j]);
  }
  
  cout<<"Data size:"<<(tDataArray[0].tVector.size())<<endl;//------------------

//threads----------------------------------------------------------------------
pthread_t threads[NUM_THREADS];

int tThread[NUM_THREADS];//thread handle

//starting threads
for (int t=0;t<NUM_THREADS;++t){

    // thread starter
    tThread[t] = pthread_create(&threads[t],NULL,sorterThreadCaller, &tDataArray[t]);

}// end threads----------------------------------------------------------------

pthread_exit(NULL);

return EXIT_SUCCESS;
}
//-----------------------------END MAIN------------------------------------------------------

//--------------THREADS FUNCTION------------------------------------------------------------------------------------
void *sorterThreadCaller(void *inData)
{
  struct tData &dataHandle= *(struct tData*)inData;
  clock_t tTime[NUM_THREADS];

  // uint64_t tid;
  // pthread_threadid_np(NULL, &tid);
  // printf("log thread id : %llu\n", tid);

  switch(dataHandle.tId){
    case 0: {//Quick Sort
              tTime[dataHandle.tId] = clock();
              printf("Quick Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //start sorting 
              quickSort(dataHandle.tVector, 0, (dataHandle.tVector.size()-1) );
              // sorting done
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Quick Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_QuickSort.txt");
              //printf("Quick Sort: Sorted numbers written to file sorted_QuickSort.txt\n");
              break;
            }
    case 1: {//Selection Sort
              tTime[dataHandle.tId] = clock();
              printf("Selection Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              selectionSort(dataHandle.tVector);
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Selection Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_Selection.txt");
              
              break;
            }
    case 2: {//Insertion Sort
              tTime[dataHandle.tId] = clock();
              printf("Insertion Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              insertionSort(dataHandle.tVector);
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Insertion Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_Insertion.txt");
              break;
            }
    case 3: {//Bubble Sort
              tTime[dataHandle.tId] = clock();
              printf("Bubble Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              bubbleSort(dataHandle.tVector); 
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Bubble Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_Bubble.txt");
              break;
            }
    case 4: {//Shell Sort
              tTime[dataHandle.tId] = clock();
              printf("Shell Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              shellSort(dataHandle.tVector);
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Shell Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_Shell.txt");
              break;
            }
    case 5: {//Merge Sort
              tTime[dataHandle.tId] = clock();
              printf("Merge Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              mergeSort(dataHandle.tVector); 
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Merge Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_Merge.txt");
              break;
            }
    case 6: {//Heap Sort
              tTime[dataHandle.tId] = clock();
              printf("Heap Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              heapSort(dataHandle.tVector);
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Heap Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_Heap.txt");
              break;
            }
    case 7: {//Bucket Sort
              tTime[dataHandle.tId] = clock();
              printf("Bucket Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              bucketSort(dataHandle.tVector);
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Bucket Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_Bucket.txt");
              break;
            }
    case 8: {//Comb Sort
              tTime[dataHandle.tId] = clock();
              printf("Comb Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              combSort(dataHandle.tVector); 
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("Comb Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_Comb.txt");
              break;
          }
    case 9: {//C++ Library Sort
              tTime[dataHandle.tId] = clock();
              printf("C++ Library Sort started | thread: %i | pthread: %lu\n",dataHandle.tId,(unsigned long)pthread_self());
              //
              cLibrarySort(dataHandle.tVector);
              //
              tTime[dataHandle.tId]=clock()-tTime[dataHandle.tId];
              printf("C++ Library Sort Finished time: %.6f\n",(float)tTime[dataHandle.tId]/CLOCKS_PER_SEC);
              fileWriter(dataHandle.tVector,"sorted_StdLibrary.txt");
              break;
          }
  }
  pthread_exit(NULL);
}
//--------------END THREADS FUNCTION---------------------------------------------------------------------------------

//----------------------------------SORTING FUNCTIONS IMPLEMENTATIONS------------------------------------------------

//file reading function-------------------------------------------------
vector<int> fileReader(string fileName){
  vector<int>vx;
  
  int temp;
  
  ifstream fromFile;
  fromFile.open(fileName.c_str());
  
  if(fromFile.fail()) cout<<"Unable to open file to read from!";
  
    else while (fromFile>>temp) 
      if (!fromFile.eof()) vx.push_back(temp);
      
  fromFile.close();
  
  return vx;//returns a vector of numbers read from file
}//end file reading function----------------------------------------------
  
//file writing function--------------------------------------------------
void fileWriter(vector<int> &fv, string fileName){
  
  ofstream toFile;
  toFile.open(fileName.c_str());
  
  if(!toFile.fail())for(vector<int>::const_iterator i = fv.begin(); i != fv.end(); ++i) toFile << *i << '\n';
    else cout<<"Unable to write file!";
    
return;
}//end file writing function---------------------------------------------

//quicksort---------------------------------------------------------------
void quickSort(vector <int> &x, int low, int high){
  if (low<high){
    //partitioning
        int pivotElement =x.at(high);
        int wall=low-1;
        
        for (int j =low; j<high; ++j){
                      if(x.at(j) <= pivotElement){
                                  wall++;
                                  swap(x.at(wall),x.at(j));
                                  
                      }
        }
        swap(x.at(wall+1),x.at(high));
        wall++;
    //end partitioning
        quickSort(x,low,(wall-1));
        quickSort(x,(wall+1), high);
  }
return;
}//end quicksort----------------------------------------------------------
 
//selection sort---------------------------------------------------------
void selectionSort(vector <int> &y){
  int i, j, indexMin;
    
  for (i= (y.size() - 1); i > 0; i--){
                     indexMin = 0;                 
                     for (j=1; j<=i; j++)  if ( y.at(j) > y.at(indexMin) ) indexMin = j;
                    swap (y.at(indexMin),y.at(i));
  }
return;
}//end selection sort------------------------------------------------------

//insertion sort-----------------------------------------------------------
void insertionSort( vector <int> &z)
{
     int i, key=0;
     for(unsigned int j = 1; j < z.size() ; j++)    // start 1 
    {
           key = z.at(j);
           for(i = j - 1; (i >= 0) && (z.at(i) > key); i--)   // large value up
          {
                 z.at(i+1) = z.at(i);
          }
         z.at(i+1) = key;    //key into location
     }
     return;
}//end insertion sort-------------------------------------------------------

//bubble sort---------------------------------------------------------------
void bubbleSort(vector <int> &w)
{
      int flag = 1;    // set flag to 1 to start first pass

      for(unsigned int i = 1; (i < w.size()) && flag; i++){
                      flag = 0;
                      for (unsigned int j=0; j < (w.size() -1); j++){
                                      if (w.at(j+1) < w.at(j)){ //asc desc
                                                swap( w.at(j) , w.at(j+1) );
                                                flag = 1;//swap occurred.
                                      }
                      }
     }
     return;
}//end bubble sort-----------------------------------------------------------

//shell sort-----------------------------------------------------------------
void shellSort( vector <int> &sv){
     int i, flag = 1, numLength = sv.size();
     int d = numLength;
     while( flag || (d > 1)){
            flag = 0; // reset flag to 0 to check for future swaps
            d = (d+1) / 2;
            for (i = 0; i < (numLength - d); i++){
               if (sv.at(i + d) < sv.at(i)){
                          swap(sv.at(i+d), sv.at(i)); // swap positions i+d & i
                          flag = 1;  // swap occurred
              }
           }
     }
return;
}//end shell sort-------------------------------------------------------------

//merge sort------------------------------------------------------------------
void mergeSort(vector<int> &mv){ 
  // completely sorted if only contains a single element.  
  if(mv.size() == 1){  
      return;  
  }  
  //middle element in the vector  
  vector<int>::iterator middle = mv.begin() + (mv.size() / 2);  

  vector<int> left(mv.begin(), middle);  
  vector<int> right(middle, mv.end());  

  // recursive call for the two smaller vectors
  mergeSort(left);  
  mergeSort(right);  

  merge(left.begin(),left.end(), right.begin(), right.end(), mv.begin()); 
return; 
}//end merge sort--------------------------------------------------------------

//heap sort--------------------------------------------------------------------
void heapSort(vector<int> &hv){
  //stl
  make_heap ( hv.begin() , hv.end() );
  sort_heap ( hv.begin() , hv.end() );
  return;
}//end heap sort---------------------------------------------------------------

//bucket sort------------------------------------------------------------------
void bucketSort(vector<int> &bv){
  
  // Create 10 empty buckets: 0,1,2,...9 (initial digit)
  vector<int> bucket[10];//
  int numBuckets = 10;
    
    // Scan through and put elements in respective buckets by first digit
    for (unsigned int i=0; i<bv.size(); ++i) {
              int bucketIndex=floor(bv.at(i)/DATA_DIGITS);//!PER DATA_DIGITS
                    bucket[bucketIndex].push_back(bv.at(i));
  }
    
    //Sort each bucket
    for (int i=0;i!=numBuckets;++i)sort(bucket[i].begin(), bucket[i].end());
 
    //Concatenate buckets 
    int index = 0;
  for (int i = 0;i!=numBuckets;++i)
    for(unsigned int j=0;j<bucket[i].size();j++) bv.at(index++)=bucket[i].at(j);
return;
}//end bucket sort-------------------------------------------------------------

//comb sort--------------------------------------------------------------------
void combSort(vector<int> &cv){
  
  int len = cv.size(), gap=len;

  bool swapped;
  do{
    swapped = false;
    
    gap /= 1.3;
    if(gap == 9 || gap == 10) gap = 11;
    if(gap < 1) gap= 1;
  
    for(int i=0; i < len-gap; ++i){
      if(cv[i] > cv[i+gap]){
        swapped = true;
        swap(cv[i], cv[i+gap]);
      }
    }
  }while(gap > 1 || swapped);
}//end comb sort-----------------------------------------------------------------

//c++ library sort---------------------------------------------------------------
void cLibrarySort(vector<int> &av){  

  sort(av.begin(), av.end());

return;
}//end c++ library sort----------------------------------------------------------

//---------------------------------END SORTING FUNCTIONS IMPLEMENTATIONS-------------------------------------------------
