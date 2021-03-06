#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int T,N,M,C,R;
vector<vector<char> > grid(100, vector<char>(100));
vector<int> used_row(100);
vector<int> used_col(100);
vector<int> used_diag1(200);
vector<int> used_diag2(100);
vector<int> used_diag2_negative(100);

void init(void){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			grid[i][j] = '.';
		}
	}
	fill(used_row.begin(), used_row.end(), 0);
	fill(used_col.begin(), used_col.end(), 0);
	fill(used_diag1.begin(), used_diag1.end(), 0);
	fill(used_diag2.begin(), used_diag2.end(), 0);
	fill(used_diag2_negative.begin(), used_diag2_negative.end(), 0);
	return;
}

int main(){
	char sym;
	int ans;
	int elem;
	int nr_case = 1;
	cin >> T;
	while(T--){
		cin >> N >> M;
		ans = 0;
		elem = 0;
		init();
		for(int i=0;i<M;i++){
			cin >> sym >> R >> C;
			R--;
			C--;
			grid[R][C] = sym;
			if(sym == 'x' || sym == 'o'){
				used_row[R] = 1;
				used_col[C] = 1;
				ans++;
			}
			if(sym == '+' || sym == 'o'){
				used_diag1[R+C] = 1;
				if(R-C>=0){
					used_diag2[R-C] = 1;
				}
				else{
					used_diag2_negative[C-R] = 1;
				}
				ans++;
			}

		}
		//processing for x and +
		vector<pair<pair<int,int>, char> > out;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
                int unique_elem = 0;
                if(used_row[i]==0 && used_col[j]==0){
                    ans++;
                    used_row[i] = 1;
                    used_col[i] = 1;
                    unique_elem++;
                    if(grid[i][j]=='.'){
                        grid[i][j] = 'x';
                    }
                    else{
                        grid[i][j] = 'o';
                    }
                }
                if(used_diag1[i+j]==0){
                    if(i-j>=0 && used_diag2[i-j]==0){
                        used_diag1[i+j] = 1;
                        used_diag2[i-j] = 1;
                        ans++;
                        unique_elem++;
                        if(grid[i][j]=='.'){
                            grid[i][j] = '+';
                        }
                        else{
                            grid[i][j] = 'o';
                        }
                    }
                    else if(i-j<0 && used_diag2_negative[j-i]==0){
                        used_diag1[i+j] = 1;
                        used_diag2_negative[j-i] = 1;
                        ans++;
                        unique_elem++;
                        if(grid[i][j]=='.'){
                            grid[i][j] = '+';
                        }
                        else{
                            grid[i][j] = 'o';
                        }
                    }
                    else{
                        //do nothing
                    }
                }
                elem+=min(1,unique_elem);
                if(unique_elem>0){
                    pair<int, int> p1(i+1,j+1);
                    pair<pair<int, int>, char> p2(p1, grid[i][j]);
                    out.push_back(p2);
                }
			}
		}
		cout << "Case #" << nr_case << ": " << ans << " " << elem << endl;
		for(int i=0;i<out.size();i++){
            cout << out[i].second << " " << out[i].first.first << " " << out[i].first.second << endl;
		}
		nr_case++;
	}
	return 0;
}
