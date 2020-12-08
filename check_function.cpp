bool check(int req_ans[][9],int user_ans[][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(req_ans[i][j] != user_ans[i][j]) {
                return false;
            }
        }
    }
    return true;
}
