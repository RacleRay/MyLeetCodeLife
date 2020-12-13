package engine

type ConcurrentEngine struct {
	Scheduler        Scheduler
	WorkerCount      int
	ItemChan         chan Item
	RequestProcessor Processor
}

type Processor func(Request) (ParseResult, error)

type Scheduler interface {
	Submit(Request)
	WorkerChan() chan Request
	// ConfigureWorkerChan(chan Request)
	// WorkerReady(chan Request)
	ReadyNotifier
	Run()
}

type ReadyNotifier interface {
	WorkerReady(chan Request)
}

func (c *ConcurrentEngine) Run(seeds ...Request) {
	// in := make(chan Request)
	out := make(chan ParseResult)
	c.Scheduler.Run()

	for i := 0; i < c.WorkerCount; i++ {
		c.createWorker(c.Scheduler,
			c.Scheduler.WorkerChan(), out)
	}

	for _, r := range seeds {
		c.Scheduler.Submit(r)
	}

	for {
		result := <-out
		for _, item := range result.Items {
			// log.Printf("Got item: %v", item)
			go func() { c.ItemChan <- item }()
		}
		for _, request := range result.Request {
			c.Scheduler.Submit(request)
		}
	}
}

func (c *ConcurrentEngine) createWorker(ready ReadyNotifier,
	in chan Request, out chan ParseResult) {
	go func() {
		for {
			ready.WorkerReady(in)
			request := <-in
			result, err := c.RequestProcessor(request)
			if err != nil {
				continue
			}
			out <- result
		}
	}()
}
