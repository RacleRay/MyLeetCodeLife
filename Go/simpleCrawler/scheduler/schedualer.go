package scheduler

import "simpleCrawler/engine"

type SimpleScheduler struct {
	workerChan chan engine.Request
}

// 使用go routine进行任务提交，防止程序中止
func (s *SimpleScheduler) Submit(r engine.Request) {
	go func() { s.workerChan <- r }()
}

// func (s *SimpleScheduler) ConfigureWorkerChan(
// 	c chan engine.Request) {
// 	s.workerChan = c
// }

func (s *SimpleScheduler) WorkerReady(chan engine.Request) {}

func (s *SimpleScheduler) WorkerChan() chan engine.Request {
	return s.workerChan
}

func (s *SimpleScheduler) Run() {
	s.workerChan = make(chan engine.Request)
}
