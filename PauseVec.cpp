#include "PauseVec.h"
#include <stdexcept>  

PauseVec* create_pausevec(){
  return new PauseVec();
}


//constructor
PauseVec::PauseVec(){
  cap=1;
  numLeft = 0;
  minRemovedInd = 0;
  removed = new bool[cap];
  data = new int[cap];

  
}

//deconstructor
PauseVec::~PauseVec(){
  delete[] data;
  delete[] removed;

}


size_t PauseVec::capacity() const{
  return cap;
}



//find how many elemnets are left. return amount 
size_t PauseVec::count() const{
  size_t count = 0;

  for(size_t i = 0; i<numLeft; i++){
    if(!removed[i]){
      count++;
    }
  }
  return count;
}




//is the index in the array?? check to see
int PauseVec::lookup(size_t index){
//index greater than the emount of elemnts in the array 
  if(index>= numLeft){
    throw std::out_of_range("Index out of range.");
  }
//if removed
  if(removed[index]){
    throw std::out_of_range("Index out of range.");
  }


  //shift elements 
  if (index> minRemovedInd){
    for (size_t i = minRemovedInd; i<= index; i++){
      if (removed[i]){
        for(size_t j=i; j<numLeft -1; j++){
          data[j] = data[j+1];
          removed[j] = removed [j+1];
        }
        numLeft--;
        while (minRemovedInd < numLeft && !removed[minRemovedInd]) {
          minRemovedInd++;
        }
        i--;

      }
    }
  }
  return data[index];
}

//remove vale at index inputed
int  PauseVec::remove(size_t index){

  //in range?
  if(index>= numLeft){
    throw std::out_of_range("Index out of range.");
  }

  if(removed[index]){
    throw std::out_of_range("Index out of range.");
  }


  int value = data[index];
  removed[index]=true;
  if (index<minRemovedInd){
    minRemovedInd = index;

  }


  


  if(count() <=cap / 4 ){
    size_t newCap = cap/2;
    int* newData = new int[newCap];
    bool* newRemoved = new bool[newCap];

    size_t j =0;
    for (size_t i =0; i<numLeft; i++){
      if(!removed[i]){
        newData[j]=data[i];
        newRemoved[j] = false;
        j++;
      }
    }
    delete[] data;
    delete [] removed;
    data = newData;
    removed = newRemoved;
    cap = newCap;
    numLeft = j;
    minRemovedInd = 0;
  }


  return value;
}





void	 PauseVec::remove_val(int x){
  for(size_t i=0; i <numLeft; i++){
    if(!removed[i] && data[i] == x){
      remove(i);
      return;
    }
    
  }


}




void   PauseVec::append(int value){
  if(numLeft == cap){
    size_t newCap = cap * 2;
    int* newData = new int [ newCap];
    bool* newRemoved = new bool [newCap];
    for ( size_t i = 0; i<numLeft ; i++){
      newData [ i] = data[i];
      newRemoved [ i] = removed[i];

    }
    delete [] data;
    delete [] removed; 
    data = newData;
    removed = newRemoved;
    cap = newCap;
  }
  data[numLeft]=value;
  removed[numLeft]=false;
  numLeft ++;



}
  




