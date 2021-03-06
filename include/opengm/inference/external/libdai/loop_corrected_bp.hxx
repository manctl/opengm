#ifndef OPENGM_LIBDAI_LOOP_CORRECTED_BP_HXX 
#define OPENGM_LIBDAI_LOOP_CORRECTED_BP_HXX
#include "opengm/inference/external/libdai/inference.hxx"

namespace opengm{
namespace external{
namespace libdai{  
   
class None{
   struct Parameter{
      Parameter() {
      }
   };
};
 
template<class GM,class ACC,class CAVITY_INFERENCE>
class LoopCorrectedBp : public LibDaiInference<GM,ACC>
{
   public:
      typedef typename CAVITY_INFERENCE::Parameter CavityInferenceParameter;
      enum UpdateRule{
         SEQFIX,
         SEQRND
      };
      enum Cavity{
         FULL,
         PAIR,
         PAIR2,
         UNIFORM
      };
      std::string name() {
         return "libDAI-Loop-Corrected-Bp";
      }
      
      struct 
      //LC[cavity=FULL,reinit=1,updates=SEQFIX,maxiter=10000,cavainame=BP,cavaiopts=[updates=SEQMAX,tol=1e-9,maxiter=10000,logdomain=0],tol=1e-9]
      struct Parameter{
         Parameter
         (
            const Cavity cavity,
            const size_t reinit
            const UpdateRule updateRule
            const size_t maxiter=10000,
            const CavityInferenceParameter & cavityInferenceParam =CavityInferenceParameter(),
            const double tolerance=1e-9,
            const size_t verbose=0
         ) :cavity_(cavity),
            reinit_(reinit),
            updateRule_(updateRule),
            maxiter_(maxiter),
            cavityInferenceParam_(cavityInferenceParam),
            tolerance_(tolerance),
            verbose_(verbose) {
         }
         std::string toString()const{
            std::string ur,cav,cavAiName,cavAiOpts;
            if(updateRule_==SEQFIX)ur = "SEQFIX";
            else if(updateRule_==SEQRND)ur = "SEQRND";
            
            if(cavity_==FULL)cav = "FULL";
            else if(cavity_==PAIR)cav = "PAIR";
            else if(cavity_==PAIR2)cav = "PAIR2";
            else if(cavity_==UNIFORM)cav = "UNIFORM";
            
            std::string cavAiAsString =cavityInferenceParam.toString();
            size_t counter=0;
            if(opengm::meta::Compare<CAVITY_INFERENCE,opengm::external::libdai::None>::value) {
               cavAiName="NONE";
               cavAiOpts="[]";
            }
            while(CAVITY_INFERENCE[i]!=']') {
               cavAiName.push_back(cavAiAsString[i]);
               ++counter;
            }
            cavAiOpts.reserve(cavAiAsString.size()-cavAiName.size());
            for(;counter<cavAiAsString.size();++counter) {
               cavAiOpts.push_back(cavAiAsString[counter]);
            }
            
            std::stringstream ss;
            ss <<"LC["
               <<"cavity="<<cav<<","
               <<"reinit="<<reinit_<<","
               <<"updates="<<ur<<","
               <<"maxiter="<<maxiter_<<","
               <<"cavainame="<<cavAiName<<","
               <<"cavaiopts="<<cavAiOpts<<","
               <<"verbose="<<verbose_<<"]";
            return ss.str();
         }
         Cavity cavity_;
         size_t reinit_;
         UpdateRule updateRule_;
         size_t maxiter_;
         CavityInferenceParameter cavityInferenceParam_;
         double tolerance_;
         size_t verbose_;
         size_t logDomain_;
      };
      LoopCorrectedBp(const GM & gm,const Parameter param=Parameter())
      :LibDaiInference<GM,ACC>(gm,param.toString()) {
         
      }

};

} // end namespace libdai
} // end namespace external
} //end namespace opengm

#endif // OPENGM_LIBDAI_LOOP_CORRECTED_BP_HXX 