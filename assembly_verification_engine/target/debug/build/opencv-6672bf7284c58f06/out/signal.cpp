#include "ocvrs_common.hpp"
#include <opencv2/signal.hpp>
#include "signal_types.hpp"

extern "C" {
void cv_signal_resampleSignal_const__InputArrayR_const__OutputArrayR_const_int_const_int(const cv::_InputArray* inputSignal, const cv::_OutputArray* outSignal, const int inFreq, const int outFreq, ResultVoid* ocvrs_return) {
	try {
		cv::signal::resampleSignal(*inputSignal, *outSignal, inFreq, outFreq);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

}
