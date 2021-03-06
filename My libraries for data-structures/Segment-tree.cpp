/* Extended class version of segment tree implementation
 * Copyright (C) bulletcross (Vishal Keshav)

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

#define INT_MAX_OPS 0
#define INT_MIN_OPS 1
#define INT_SUM_OPS 2

#define DEBUG

class seg_tree{
	public:
		seg_tree(vector<int> vec, int operation){
			nr_elem = vec.size();
			ops = operation;
			input_vec = vec;
			tree_size = (int)(2 * pow(2.0, floor((log((double)nr_elem) / log(2.0)) + 1)));
			segment_tree.resize(tree_size,0);
			init_segment_tree(1,0,nr_elem-1);
		}
		int query(int s_index, int e_index){
			return query_util(1,0,nr_elem-1,s_index,e_index);
		}
		void update(int new_val, int index){
			//Check for errors
			if(!(index<nr_elem)){
				return;
			}
			input_vec[index] = new_val;
			update_util(1,0,nr_elem-1,new_val,index);
		}

	private:
		int nr_elem;
		int tree_size,ops;
		vector<int> segment_tree;
		vector<int> input_vec;

		void init_segment_tree(int node, int start_index, int end_index){
			if(start_index == end_index){
				if(ops==INT_MIN_OPS || ops==INT_MAX_OPS){
					segment_tree[node] = start_index;
				}
				else{
					segment_tree[node] = input_vec[start_index];
				}
			}
			else{
				int left_child = 2*node;
				int right_child = 2*node + 1;
				init_segment_tree(left_child, start_index, (start_index+end_index)/2);
				init_segment_tree(right_child, (start_index+end_index)/2 + 1, end_index);
				int left_result = segment_tree[left_child];
				int right_result = segment_tree[right_child];

				if(ops==INT_SUM_OPS){
					segment_tree[node] = left_result + right_result;
				}
				else{
					int left_value = input_vec[left_result];
					int right_value = input_vec[right_result];
					if(ops==INT_MAX_OPS){
						segment_tree[node] = (left_value>=right_value)? left_result:right_result;
					}
					else{
						segment_tree[node] = (left_value<=right_value)? left_result:right_result;
					}
				}
			}
		}

		int query_util(int node, int interval_start, int interval_end, int i, int j){
			if(i>interval_end || j<interval_start){
				return -1;
			}
			if(interval_start>=i && interval_end <=j){
				return segment_tree[node];
			}

			int pos1 = query_util(2*node,interval_start, (interval_start+interval_end)/2, i, j);
			int pos2 = query_util(2*node + 1, (interval_start+interval_end)/2 + 1, interval_end, i, j);
			if(pos1==-1){
				return pos2;
			}
			if(pos2==-1){
				return pos1;
			}

			switch(ops){
				case INT_MAX_OPS:
					return input_vec[pos1]>=input_vec[pos2]? pos1:pos2;
				case INT_MIN_OPS:
					return input_vec[pos1]<=input_vec[pos2]? pos1:pos2;
				case INT_SUM_OPS:
					return pos1+pos2;
			}
		}
		void update_util(int node, int s_index, int e_index, int new_val, int index){
			if(s_index == e_index){
                if(ops==INT_SUM_OPS){
                    segment_tree[node] = new_val;
                }
			}
			else{
				int mid_index = (e_index + s_index)/2;
				if(s_index <= index && index <= mid_index){
					update_util(2*node, s_index, mid_index, new_val, index);
				}
				else{
					update_util(2*node+1, mid_index+1, e_index, new_val, index);
				}
				int left = segment_tree[2*node];
				int right = 2*node+1 < tree_size?segment_tree[2*node+1]:-1;
				switch(ops){
					case INT_MAX_OPS:
						segment_tree[node] = (right==-1)?left:((input_vec[left]<input_vec[right])?right:left);
						break;
					case INT_MIN_OPS:
						segment_tree[node] = (right==-1)?left:((input_vec[left]<input_vec[right])?left:right);
						break;
					case INT_SUM_OPS:
						segment_tree[node] = (right==-1)?left:(left+right);
						break;
				}
			}
			return;
		}
};

int main(){
#ifdef DEBUG
	vector<int> vec = {8, 7, 3, 9, 5, 1, 10};
	seg_tree sg(vec,1);
	cout << sg.query(1,1) << " "  << sg.query(2,3) << " " << sg.query(4,6)<<" " << sg.query(3,4)<< endl;
    sg.update(1,3);
    cout << sg.query(1,1) << " "  << sg.query(2,3) << " " << sg.query(4,6)<<" " << sg.query(3,4)<< endl;
#endif
	return 0;
}
