vector<int> z_fun(string s)
{
    int n = s.size();
    vector<int> ans(n, 0);
    int l = 0, r = 1;
    for(int i=1; i<n; i++)
    {
        if(i<r)
        {
            ans[i] = min(r-i, ans[i-l]);    
        }
        while(i+ans[i]<n && s[i+ans[i]]==s[ans[i]])
        {
            ans[i]++;
        }
        if(i+ans[i]>r)
        {
            r = i + ans[i];
            l = i;
        }
    }
    return ans;
}
