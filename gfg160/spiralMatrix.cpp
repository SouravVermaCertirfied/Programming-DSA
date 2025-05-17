class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int rows        = matrix.size();
        int cols        = matrix[0].size();
        int sizee       = rows * cols;
        int count       = 0;
        int direction   = 0;
        int leftbound   = 0;
        int upbound     = 0;
        int rightbound  = cols - 1;
        int downbound   = rows - 1;
        int i = 0;
        int j = 0;
        vector<int> ans;
        while(count<sizee){
            switch(direction){
                case 0:{
                        while(j<=rightbound){
                            ans.push_back(matrix[i][j]);
                            count++;
                            j++;
                        }
                        j--;
                        i++;
                        upbound++;
                        break;
                }
                case 1:{
                        while(i<=downbound){
                            ans.push_back(matrix[i][j]);
                            count++;
                            i++;
                        }
                        i--;
                        j--;
                        rightbound--;
                        break;
                }
                case 2:{
                        while(j>=leftbound){
                            ans.push_back(matrix[i][j]);
                            count++;
                            j--;
                        }
                        j++;
                        i--;
                        downbound--;
                        break;
                }
                case 3:{
                        while(i>=upbound){
                            ans.push_back(matrix[i][j]);
                            count++;
                            i--;
                        }
                        i++;
                        j++;
                        leftbound++;
                        break;
                }
                default:
                    break;

            }
            direction = ( direction + 1 ) % 4;
            
        }
        return ans;
    }
};