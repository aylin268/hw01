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
  size_t count = 0;

  for(size_t i =0; i<numLeft; i++){
    if(!removed[i]){
      if(count==index){
        return data[i];
      }
      count++;
    }
  } 
      
  throw std::out_of_range("Index out of range.");
}


//remove vale at index inputed
int  PauseVec::remove(size_t index){
  size_t count =0;
  for(size_t i =0; i<numLeft; i++){
    if(!removed[i]){
      if(count==index){
        int value = data[i];
        removed[i] = true;
      
        if(i<minRemovedInd){
            minRemovedInd = i;
        }
        if(this->count() <=cap / 4 && cap>1){
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
          for (size_t k = j; k < newCap; k++) {
            newRemoved[k] = false;
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
      count++;
    }
  }
  throw std::out_of_range("Index out of range.");
}






void	 PauseVec::remove_val(int x){
  size_t count = 0;
  
  for(size_t i=0; i <numLeft; i++){
    if(!removed[i]){
      if(data[i] == x){
        remove(count);
        return;
       }
      count++;
    
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
   
