package scheduler

import "simpleCrawler/engine"

type QueueScheduler struct {
	// engine到scheduler的连接
	requestChan chan engine.Request
	// scheduler到worker的连接
	workerChan chan chan engine.Request
}

func (s *QueueScheduler) Submit(r engine.Request) {
	s.requestChan <- r
}

// 暴露出可使用的worker
func (s *QueueScheduler) WorkerReady(w chan engine.Request) {
	s.workerChan <- w
}

// func (s *QueueScheduler) ConfigureWorkerChan(chan engine.Request) {}

func (s *QueueScheduler) WorkerChan() chan engine.Request {
	return make(chan engine.Request)
}

func (s *QueueScheduler) Run() {
	s.requestChan = make(chan engine.Request)
	s.workerChan = make(chan chan engine.Request)
	go func() {
		var requestQueue []engine.Request
		var workerQueue []chan engine.Request
		for {
			var activeRequest engine.Request
			var activeWorker chan engine.Request
			if len(requestQueue) > 0 && len(workerQueue) > 0 {
				activeRequest = requestQueue[0]
				activeWorker = workerQueue[0]
			}
			select {
			case r := <-s.requestChan:
				requestQueue = append(requestQueue, r)
			case w := <-s.workerChan:
				workerQueue = append(workerQueue, w)
			// 若为nil 不会执行
			case activeWorker <- activeRequest:
				workerQueue = workerQueue[1:]
				requestQueue = requestQueue[1:]
			}
		}
	}()
}
