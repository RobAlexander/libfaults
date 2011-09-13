TODO
====

- Replace all different FaultModels in libfaults with a single FaultModel. The
  single model loads a Lua script which handles GetFaulty. This should mean we
  can strip out 90% of code from faultyposition2d::initFaultModel, and make it
  much more flexible. Performance shouldn't be an issue if LuaJIT is used.

- More advanced models may need some concept of real/simulation time. We'll need
  some way of passing this in...
