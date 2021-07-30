class Solution:
    def minimumTotal(self, triangle):
        # 1e4 * 200 + change
        INFTY = 100000000
        dp = [[INFTY for _ in r] for r in triangle]
        dp[0][0] = triangle[0][0]
        
        for r in range(0, len(triangle)-1): 
            for c in range(r+1):
                print("(%s, %s)" % (r, c))
                dp[r+1][c] = min(dp[r+1][c], dp[r][c] + triangle[r+1][c])
                dp[r+1][c+1] = min(dp[r+1][c+1], dp[r][c] + triangle[r+1][c+1])
        print(dp)
        best = min(dp[-1])
        return best

if __name__ == "__main__":
    x = Solution()
    print(x.minimumTotal([[2],[3,4],[6,5,7],[4,1,8,3]]))
