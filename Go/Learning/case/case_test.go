package main

import "testing"

// go test
// go test -coverprofile c.out
// go tool cover -html c.out
func TestSubstr(t *testing.T) {
	tests := []struct {
		s   string
		ans int
	}{
		// Normal cases
		{"abcabcbb", 3},
		{"pwwkew", 3},

		// Edge cases
		{"", 0},
		{"b", 1},
		{"bbbbbbbbb", 1},
		{"abcabcabcd", 4},

		// Chinese support
		{"这里是慕课网", 6},
		{"一二三二一", 3},
		{"黑化肥挥发发灰会花飞灰化肥挥发发黑会飞花", 8},
	}
	for _, tt := range tests {
		result := lenCompute(tt.s)
		if tt.ans != result {
			t.Errorf("got %d for input %s; "+
				"expected %d",
				result, tt.s, tt.ans)
		}
	}
}

// go test -bench .
// go test -bench . -cpuprofile cpu.out
// go tool pprof cpu.out
// web
// quit
func BenchmarkSubstr(b *testing.B) {
	s := "黑化肥挥发发灰会花飞灰化肥挥发发黑会飞花"
	for i := 0; i < 13; i++ {
		s = s + s
	}
	b.Logf("len(s) = %d", len(s))
	ans := 8
	b.ResetTimer()

	for i := 0; i < b.N; i++ {
		result := lenCompute(s)
		if ans != result {
			b.Errorf("got %d for input %s; "+
				"expected %d",
				result, s, ans)
		}
	}
}
