#include<iostream>
#include<cstdlib>
#include<vector>
#include<chrono>
#include<thread>
#include<fstream>

//game board class
class state{
public:
  int N, M; //M is number of rows, N number of columns
  std::vector<std::vector<bool> > board; //1 is alive, 0 is dead
  int liveNeighbors(int x, int y);
  void tick(state &x);
  void print();
};

//function to count the number of live neighbors
int state::liveNeighbors(int x, int y){
  int c = 0;
  int lx,ly,ux,uy;
  lx = -1;
  ly = -1;
  ux = 1;
  uy = 1;

  if(x == 0)
    lx = 0;

  if(y == 0)
    ly = 0;

  if(x == N-1)
    ux = 0;

  if(y == M-1)
    uy = 0;

  for(int i = lx; i <= ux; i++){
    for(int j = ly; j <= uy; j++){
      if(i == 0 && j==0)
	continue;
      if(board.at(x + i).at(y + j) == 1)
	c++;
    }
  }
  return c;
}

void state::print(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){ //i is the row index, j is the column index
      std::cout << board.at(i).at(j) << ' ';
      if(j == N-1)
	std::cout << '\n';
    }
  }
}

void state::tick(state &x){
  state temp = x;
  for(int i = 0; i < N; i++){ //which column we are in
    for(int j = 0; j < M; j++){ //which row
      if(x.board.at(i).at(j) == 1){
	if(x.liveNeighbors(i,j) < 2)
	  temp.board.at(i).at(j) = 0;
	if(x.liveNeighbors(i,j) > 3)
	  temp.board.at(i).at(j) = 0;
      }
      else
	if(x.liveNeighbors(i,j) == 3)
	  temp.board.at(i).at(j) = 1;
    }
  }
  x = temp;
}


int main(){
  
  //set the initial game board dimensions
  

  state init;

  init.M = 40;
  init.N = 40;
  std::vector<bool> zero;
  zero.assign(init.M,0);
  init.board.assign(init.N,zero);

  std::ifstream input("game_board.txt");

  for(int i = 0; i < init.N; i++){
    for(int j = 0; j < init.M; j++){
      bool a;
      input >> a;
      init.board.at(i).at(j) = a;
    }
  }

  init.print();
  std::cout << '\n';

  for(int i = 0; i < 60; i++){
    init.tick(init);
    init.print();
    std::cout << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}

  


    


  
  

  

