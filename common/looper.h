#ifndef COMMON_LOOPER_H
#define COMMON_LOOPER_H

#ifndef OSx // ProffieOS
// Helper class for classses that needs to be called back from the Loop()
// function. Also provides a Setup() function.
class Looper;
Looper* loopers = NULL;
Looper* hf_loopers = NULL;
LoopCounter global_loop_counter;
LoopCounter hf_loop_counter;
class Looper {
public:
  void Link() {
    CHECK_LL(Looper, loopers, next_looper_);
    next_looper_ = loopers;
    loopers = this;
    CHECK_LL(Looper, loopers, next_looper_);
  }
  // High-Frequency Loopers go at the end of the list
  void HighFrequencyLink() {
    CHECK_LL(Looper, loopers, next_looper_);
    Looper** i = &loopers;
    while (*i) i = &(*i)->next_looper_;
    next_looper_ = nullptr;
    *i = this;
    if (!hf_loopers) hf_loopers = this;
    CHECK_LL(Looper, loopers, next_looper_);
  }
  void Unlink() {
    CHECK_LL(Looper, loopers, next_looper_);
    if (hf_loopers == this) hf_loopers = next_looper_;
    for (Looper** i = &loopers; *i; i = &(*i)->next_looper_) {
      if (*i == this) {
        *i = next_looper_;
        CHECK_LL(Looper, loopers, next_looper_);
        return;
      }
    }
    CHECK_LL(Looper, loopers, next_looper_);
  }
  Looper() { Link(); }
  explicit Looper(NoLink _) { }
  explicit Looper(HFLink _) { HighFrequencyLink(); }
  ~Looper() { Unlink(); }
  static void DoLoop() {
    ScopedCycleCounter cc(loop_cycles);
    CHECK_LL(Looper, loopers, next_looper_);
    for (Looper *l = loopers; l; l = l->next_looper_) {
      ScopedCycleCounter cc2(l->cycles_);
      l->Loop();
    }
    global_loop_counter.Update();
    hf_loop_counter.Update();
  }
  static void DoHFLoop() {
    ScopedCycleCounter cc(loop_cycles);
    CHECK_LL(Looper, loopers, next_looper_);
    for (Looper *l = hf_loopers; l; l = l->next_looper_) {
      // TODO: We're currently double-counting these cycles, since
      // DoHfLoop() is likely to be called from inside of DoLoop()
      ScopedCycleCounter cc2(l->cycles_);
      l->Loop();
    }
    hf_loop_counter.Update();
  }
  static void DoSetup() {
    for (Looper *l = loopers; l; l = l->next_looper_) {
      l->Setup();
    }
  }
  static void LoopTop(float total_cycles) {
    for (Looper *l = loopers; l; l = l->next_looper_) {
      STDOUT.print(l->name());
      STDOUT.print(" loop: ");
      STDOUT.print(l->cycles_ * 100.0f / total_cycles);
      STDOUT.println("%");
      l->cycles_ = 0;
    }
    loop_cycles = 0;
  }
  static uint64_t CountCycles() {
    uint64_t cycles = loop_cycles;
    for (Looper *l = loopers; l; l = l->next_looper_)
      cycles += l->cycles_;
    return cycles;
  }

protected:
  virtual const char* name() = 0;
  virtual void Loop() = 0;
  virtual void Setup() {}
private:
  uint64_t cycles_ = 0;
  Looper* next_looper_;
};

#else // OSx
  class Looper;
  Looper* loopers = NULL;
  Looper* hf_loopers = NULL;
  class Looper {
  public:
    void Link() {
      scheduled_time_ = 0;
      next_looper_ = loopers;
      loopers = this;
    }
    void Link(uint32_t schmicros) {
      scheduled_time_ = schmicros;
      next_looper_ = loopers;
      loopers = this;
    }
    void Unlink() {
      scheduled_time_ = 0;
      for (Looper** i = &loopers; *i; i = &(*i)->next_looper_) {
        if (*i == this) {
          *i = next_looper_;
          return;
        }
      }
    }
    Looper() { Link();  }   // link at highest priority
    Looper(uint32_t schmicros) { Link(schmicros);  } // link and schedule at callmicros [us]
    explicit Looper(NoLink _) { }
    explicit Looper(HFLink _) { Link(); } // High-Frequency Loopers are discarded
    ~Looper() { Unlink(); }
    static void DoLoop() {
      uint32_t microsNow = micros();       // current time;
      for (Looper *l = loopers; l; l = l->next_looper_) {
        if (microsNow - l->cpu_probe_.micros >= l->scheduled_time_) {
          ScopedCycleCounter cc(l->cpu_probe_);     // updates .cpu_probe_.micros (and CPU probe if enabled)
          l->Loop();                                // run .Loop() for this task
          microsNow = micros();                     // update current loop time (changed if .Loop() run)
        }
      }
      // char * stack_ptr = (char*)__get_MSP();
      // STDOUT.print(" * Temporary RAM (stack): "); STDOUT.println((uint32_t)(0x2000C000) - (uint32_t)(stack_ptr) );

    }
    static void DoHFLoop() { }
    static void DoSetup() {
      for (Looper *l = loopers; l; l = l->next_looper_) {
        l->Setup();
      }
    }
    static void DoProbe(DoWhatToProbe what) {
      for (Looper *l = loopers; l; l = l->next_looper_) 
        if (what==DoWhatToProbe::reset_probe)
          l->cpu_probe_.Reset();        
        else {
          l->cpu_probe_.Print(what);    
          STDOUT.print(" ");        
          STDOUT.println(l->name());
        }
    }
  protected:
    virtual const char* name() = 0;
    virtual void Loop() = 0;
    virtual void Setup() {}
  private:
    xProbe cpu_probe_;        // X_PROBECPU defined: monitors execution time, call frequency and cpu usage
    uint32_t scheduled_time_; // call period, in microsecond. .Loop() will be called on time intervals >= scheduled_time_
    Looper* next_looper_;
  };
#endif // OSx
#endif
