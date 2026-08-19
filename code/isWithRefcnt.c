bool _isWithRefcnt(InstLoc *floc, InstLoc *uloc) {
    // Heuristic 1: see whether the F is inside a refcnt
    // put function.
    static std::set<std::string> put_func_inc {
        "_put",
        "put_",
    };
    static std::set<std::string> get_func_inc {
        "_get",
        "get_",
    };
    if (floc) {
        std::vector<Instruction*> insts;
        if (dyn_cast<Instruction>(floc->inst)) {
            insts.push_back(
                dyn_cast<Instruction>(floc->inst)
            );
        }
        if (floc->ctx && !floc->ctx->empty()) {
            insts.insert(
                insts.begin(),
                floc->ctx->callSites->begin(),
                floc->ctx->callSites->end()
            );
        }
        for (int i = insts.size() - 1; i >= 0; --i) {
            Instruction *inst = insts[i];
            if (inst && inst->getParent() && inst->getFunction()) {
                std::string func = inst->getFunction()->getName().str();
                for (auto &s : put_func_inc) {
                    if (func.find(s) != std::string::npos) {
                        return true;
                    }
                }
            }
            // Also check the func name from the dbg info, which can
            // even reveal the names of the inlined functions.
            if (i % 2) { 
                std::vector<std::string> fns;
                InstructionUtils::getHostFuncsFromDLoc(inst,fns);
                for (auto &fn : fns) {
                    for (auto &s : put_func_inc) {
                        if (fn.find(s) != std::string::npos) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    // Comments about heuristics 2 and 3
    return false;
}