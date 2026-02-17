#include "tracking.hpp"
#include "tracking_types.hpp"

extern "C" {
void cv_legacy_upgradeTrackingAPI_const_PtrLTrackerGR(const cv::Ptr<cv::legacy::Tracker>* legacy_tracker, Result<cv::Ptr<cv::Tracker>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::Tracker> ret = cv::legacy::upgradeTrackingAPI(*legacy_tracker);
		Ok(new cv::Ptr<cv::Tracker>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_TrackerCSRT_create_const_ParamsR(const cv::TrackerCSRT::Params* parameters, Result<cv::Ptr<cv::TrackerCSRT>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::TrackerCSRT> ret = cv::TrackerCSRT::create(*parameters);
		Ok(new cv::Ptr<cv::TrackerCSRT>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_TrackerCSRT_create(Result<cv::Ptr<cv::TrackerCSRT>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::TrackerCSRT> ret = cv::TrackerCSRT::create();
		Ok(new cv::Ptr<cv::TrackerCSRT>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_TrackerCSRT_setInitialMask_const__InputArrayR(cv::TrackerCSRT* instance, const cv::_InputArray* mask, ResultVoid* ocvrs_return) {
	try {
		instance->setInitialMask(*mask);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Tracker* cv_TrackerCSRT_to_Tracker(cv::TrackerCSRT* instance) {
		return dynamic_cast<cv::Tracker*>(instance);
}

void cv_TrackerCSRT_delete(cv::TrackerCSRT* instance) {
		delete instance;
}

void cv_TrackerCSRT_Params_Params(Result<cv::TrackerCSRT::Params*>* ocvrs_return) {
	try {
		cv::TrackerCSRT::Params* ret = new cv::TrackerCSRT::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::TrackerCSRT::Params* cv_TrackerCSRT_Params_implicitClone_const(const cv::TrackerCSRT::Params* instance) {
		return new cv::TrackerCSRT::Params(*instance);
}

bool cv_TrackerCSRT_Params_propUse_hog_const(const cv::TrackerCSRT::Params* instance) {
		bool ret = instance->use_hog;
		return ret;
}

void cv_TrackerCSRT_Params_propUse_hog_const_bool(cv::TrackerCSRT::Params* instance, const bool val) {
		instance->use_hog = val;
}

bool cv_TrackerCSRT_Params_propUse_color_names_const(const cv::TrackerCSRT::Params* instance) {
		bool ret = instance->use_color_names;
		return ret;
}

void cv_TrackerCSRT_Params_propUse_color_names_const_bool(cv::TrackerCSRT::Params* instance, const bool val) {
		instance->use_color_names = val;
}

bool cv_TrackerCSRT_Params_propUse_gray_const(const cv::TrackerCSRT::Params* instance) {
		bool ret = instance->use_gray;
		return ret;
}

void cv_TrackerCSRT_Params_propUse_gray_const_bool(cv::TrackerCSRT::Params* instance, const bool val) {
		instance->use_gray = val;
}

bool cv_TrackerCSRT_Params_propUse_rgb_const(const cv::TrackerCSRT::Params* instance) {
		bool ret = instance->use_rgb;
		return ret;
}

void cv_TrackerCSRT_Params_propUse_rgb_const_bool(cv::TrackerCSRT::Params* instance, const bool val) {
		instance->use_rgb = val;
}

bool cv_TrackerCSRT_Params_propUse_channel_weights_const(const cv::TrackerCSRT::Params* instance) {
		bool ret = instance->use_channel_weights;
		return ret;
}

void cv_TrackerCSRT_Params_propUse_channel_weights_const_bool(cv::TrackerCSRT::Params* instance, const bool val) {
		instance->use_channel_weights = val;
}

bool cv_TrackerCSRT_Params_propUse_segmentation_const(const cv::TrackerCSRT::Params* instance) {
		bool ret = instance->use_segmentation;
		return ret;
}

void cv_TrackerCSRT_Params_propUse_segmentation_const_bool(cv::TrackerCSRT::Params* instance, const bool val) {
		instance->use_segmentation = val;
}

void* cv_TrackerCSRT_Params_propWindow_function_const(const cv::TrackerCSRT::Params* instance) {
		std::string ret = instance->window_function;
		return ocvrs_create_string(ret.c_str());
}

void cv_TrackerCSRT_Params_propWindow_function_const_string(cv::TrackerCSRT::Params* instance, const char* val) {
		instance->window_function = std::string(val);
}

float cv_TrackerCSRT_Params_propKaiser_alpha_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->kaiser_alpha;
		return ret;
}

void cv_TrackerCSRT_Params_propKaiser_alpha_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->kaiser_alpha = val;
}

float cv_TrackerCSRT_Params_propCheb_attenuation_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->cheb_attenuation;
		return ret;
}

void cv_TrackerCSRT_Params_propCheb_attenuation_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->cheb_attenuation = val;
}

float cv_TrackerCSRT_Params_propTemplate_size_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->template_size;
		return ret;
}

void cv_TrackerCSRT_Params_propTemplate_size_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->template_size = val;
}

float cv_TrackerCSRT_Params_propGsl_sigma_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->gsl_sigma;
		return ret;
}

void cv_TrackerCSRT_Params_propGsl_sigma_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->gsl_sigma = val;
}

float cv_TrackerCSRT_Params_propHog_orientations_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->hog_orientations;
		return ret;
}

void cv_TrackerCSRT_Params_propHog_orientations_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->hog_orientations = val;
}

float cv_TrackerCSRT_Params_propHog_clip_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->hog_clip;
		return ret;
}

void cv_TrackerCSRT_Params_propHog_clip_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->hog_clip = val;
}

float cv_TrackerCSRT_Params_propPadding_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->padding;
		return ret;
}

void cv_TrackerCSRT_Params_propPadding_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->padding = val;
}

float cv_TrackerCSRT_Params_propFilter_lr_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->filter_lr;
		return ret;
}

void cv_TrackerCSRT_Params_propFilter_lr_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->filter_lr = val;
}

float cv_TrackerCSRT_Params_propWeights_lr_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->weights_lr;
		return ret;
}

void cv_TrackerCSRT_Params_propWeights_lr_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->weights_lr = val;
}

int cv_TrackerCSRT_Params_propNum_hog_channels_used_const(const cv::TrackerCSRT::Params* instance) {
		int ret = instance->num_hog_channels_used;
		return ret;
}

void cv_TrackerCSRT_Params_propNum_hog_channels_used_const_int(cv::TrackerCSRT::Params* instance, const int val) {
		instance->num_hog_channels_used = val;
}

int cv_TrackerCSRT_Params_propAdmm_iterations_const(const cv::TrackerCSRT::Params* instance) {
		int ret = instance->admm_iterations;
		return ret;
}

void cv_TrackerCSRT_Params_propAdmm_iterations_const_int(cv::TrackerCSRT::Params* instance, const int val) {
		instance->admm_iterations = val;
}

int cv_TrackerCSRT_Params_propHistogram_bins_const(const cv::TrackerCSRT::Params* instance) {
		int ret = instance->histogram_bins;
		return ret;
}

void cv_TrackerCSRT_Params_propHistogram_bins_const_int(cv::TrackerCSRT::Params* instance, const int val) {
		instance->histogram_bins = val;
}

float cv_TrackerCSRT_Params_propHistogram_lr_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->histogram_lr;
		return ret;
}

void cv_TrackerCSRT_Params_propHistogram_lr_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->histogram_lr = val;
}

int cv_TrackerCSRT_Params_propBackground_ratio_const(const cv::TrackerCSRT::Params* instance) {
		int ret = instance->background_ratio;
		return ret;
}

void cv_TrackerCSRT_Params_propBackground_ratio_const_int(cv::TrackerCSRT::Params* instance, const int val) {
		instance->background_ratio = val;
}

int cv_TrackerCSRT_Params_propNumber_of_scales_const(const cv::TrackerCSRT::Params* instance) {
		int ret = instance->number_of_scales;
		return ret;
}

void cv_TrackerCSRT_Params_propNumber_of_scales_const_int(cv::TrackerCSRT::Params* instance, const int val) {
		instance->number_of_scales = val;
}

float cv_TrackerCSRT_Params_propScale_sigma_factor_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->scale_sigma_factor;
		return ret;
}

void cv_TrackerCSRT_Params_propScale_sigma_factor_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->scale_sigma_factor = val;
}

float cv_TrackerCSRT_Params_propScale_model_max_area_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->scale_model_max_area;
		return ret;
}

void cv_TrackerCSRT_Params_propScale_model_max_area_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->scale_model_max_area = val;
}

float cv_TrackerCSRT_Params_propScale_lr_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->scale_lr;
		return ret;
}

void cv_TrackerCSRT_Params_propScale_lr_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->scale_lr = val;
}

float cv_TrackerCSRT_Params_propScale_step_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->scale_step;
		return ret;
}

void cv_TrackerCSRT_Params_propScale_step_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->scale_step = val;
}

float cv_TrackerCSRT_Params_propPsr_threshold_const(const cv::TrackerCSRT::Params* instance) {
		float ret = instance->psr_threshold;
		return ret;
}

void cv_TrackerCSRT_Params_propPsr_threshold_const_float(cv::TrackerCSRT::Params* instance, const float val) {
		instance->psr_threshold = val;
}

void cv_TrackerCSRT_Params_delete(cv::TrackerCSRT::Params* instance) {
		delete instance;
}

void cv_TrackerKCF_create_const_ParamsR(const cv::TrackerKCF::Params* parameters, Result<cv::Ptr<cv::TrackerKCF>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::TrackerKCF> ret = cv::TrackerKCF::create(*parameters);
		Ok(new cv::Ptr<cv::TrackerKCF>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_TrackerKCF_create(Result<cv::Ptr<cv::TrackerKCF>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::TrackerKCF> ret = cv::TrackerKCF::create();
		Ok(new cv::Ptr<cv::TrackerKCF>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_TrackerKCF_setFeatureExtractor_FeatureExtractorCallbackFN_bool(cv::TrackerKCF* instance, cv::TrackerKCF::FeatureExtractorCallbackFN callback, bool pca_func, ResultVoid* ocvrs_return) {
	try {
		instance->setFeatureExtractor(callback, pca_func);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_TrackerKCF_setFeatureExtractor_FeatureExtractorCallbackFN(cv::TrackerKCF* instance, cv::TrackerKCF::FeatureExtractorCallbackFN callback, ResultVoid* ocvrs_return) {
	try {
		instance->setFeatureExtractor(callback);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Tracker* cv_TrackerKCF_to_Tracker(cv::TrackerKCF* instance) {
		return dynamic_cast<cv::Tracker*>(instance);
}

void cv_TrackerKCF_delete(cv::TrackerKCF* instance) {
		delete instance;
}

void cv_TrackerKCF_Params_Params(Result<cv::TrackerKCF::Params>* ocvrs_return) {
	try {
		cv::TrackerKCF::Params ret;
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeature_create_const_StringR(const char* trackerFeatureType, Result<cv::Ptr<cv::detail::TrackerContribFeature>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::detail::TrackerContribFeature> ret = cv::detail::TrackerContribFeature::create(std::string(trackerFeatureType));
		Ok(new cv::Ptr<cv::detail::TrackerContribFeature>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeature_selection_MatR_int(cv::detail::TrackerContribFeature* instance, cv::Mat* response, int npoints, ResultVoid* ocvrs_return) {
	try {
		instance->selection(*response, npoints);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeature_getClassName_const(const cv::detail::TrackerContribFeature* instance, Result<void*>* ocvrs_return) {
	try {
		cv::String ret = instance->getClassName();
		Ok(ocvrs_create_string(ret.c_str()), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribFeatureHAAR* cv_detail_TrackerContribFeature_to_Detail_TrackerContribFeatureHAAR(cv::detail::TrackerContribFeature* instance) {
		return dynamic_cast<cv::detail::TrackerContribFeatureHAAR*>(instance);
}

cv::detail::TrackerFeatureFeature2d* cv_detail_TrackerContribFeature_to_Detail_TrackerFeatureFeature2d(cv::detail::TrackerContribFeature* instance) {
		return dynamic_cast<cv::detail::TrackerFeatureFeature2d*>(instance);
}

cv::detail::TrackerFeatureHOG* cv_detail_TrackerContribFeature_to_Detail_TrackerFeatureHOG(cv::detail::TrackerContribFeature* instance) {
		return dynamic_cast<cv::detail::TrackerFeatureHOG*>(instance);
}

cv::detail::TrackerFeatureLBP* cv_detail_TrackerContribFeature_to_Detail_TrackerFeatureLBP(cv::detail::TrackerContribFeature* instance) {
		return dynamic_cast<cv::detail::TrackerFeatureLBP*>(instance);
}

cv::detail::TrackerFeature* cv_detail_TrackerContribFeature_to_Detail_TrackerFeature(cv::detail::TrackerContribFeature* instance) {
		return dynamic_cast<cv::detail::TrackerFeature*>(instance);
}

void cv_detail_TrackerContribFeature_delete(cv::detail::TrackerContribFeature* instance) {
		delete instance;
}

void cv_detail_TrackerContribFeatureHAAR_TrackerContribFeatureHAAR_const_ParamsR(const cv::detail::TrackerContribFeatureHAAR::Params* parameters, Result<cv::detail::TrackerContribFeatureHAAR*>* ocvrs_return) {
	try {
		cv::detail::TrackerContribFeatureHAAR* ret = new cv::detail::TrackerContribFeatureHAAR(*parameters);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureHAAR_TrackerContribFeatureHAAR(Result<cv::detail::TrackerContribFeatureHAAR*>* ocvrs_return) {
	try {
		cv::detail::TrackerContribFeatureHAAR* ret = new cv::detail::TrackerContribFeatureHAAR();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureHAAR_extractSelected_const_vectorLintG_const_vectorLMatGR_MatR(cv::detail::TrackerContribFeatureHAAR* instance, const std::vector<int>* selFeatures, const std::vector<cv::Mat>* images, cv::Mat* response, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->extractSelected(*selFeatures, *images, *response);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureHAAR_selection_MatR_int(cv::detail::TrackerContribFeatureHAAR* instance, cv::Mat* response, int npoints, ResultVoid* ocvrs_return) {
	try {
		instance->selection(*response, npoints);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureHAAR_swapFeature_int_int(cv::detail::TrackerContribFeatureHAAR* instance, int source, int target, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->swapFeature(source, target);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribFeature* cv_detail_TrackerContribFeatureHAAR_to_Detail_TrackerContribFeature(cv::detail::TrackerContribFeatureHAAR* instance) {
		return dynamic_cast<cv::detail::TrackerContribFeature*>(instance);
}

cv::detail::TrackerFeature* cv_detail_TrackerContribFeatureHAAR_to_Detail_TrackerFeature(cv::detail::TrackerContribFeatureHAAR* instance) {
		return dynamic_cast<cv::detail::TrackerFeature*>(instance);
}

void cv_detail_TrackerContribFeatureHAAR_delete(cv::detail::TrackerContribFeatureHAAR* instance) {
		delete instance;
}

void cv_detail_TrackerContribFeatureHAAR_Params_Params(Result<cv::detail::TrackerContribFeatureHAAR::Params*>* ocvrs_return) {
	try {
		cv::detail::TrackerContribFeatureHAAR::Params* ret = new cv::detail::TrackerContribFeatureHAAR::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

int cv_detail_TrackerContribFeatureHAAR_Params_propNumFeatures_const(const cv::detail::TrackerContribFeatureHAAR::Params* instance) {
		int ret = instance->numFeatures;
		return ret;
}

void cv_detail_TrackerContribFeatureHAAR_Params_propNumFeatures_const_int(cv::detail::TrackerContribFeatureHAAR::Params* instance, const int val) {
		instance->numFeatures = val;
}

void cv_detail_TrackerContribFeatureHAAR_Params_propRectSize_const(const cv::detail::TrackerContribFeatureHAAR::Params* instance, cv::Size* ocvrs_return) {
		cv::Size ret = instance->rectSize;
		*ocvrs_return = ret;
}

void cv_detail_TrackerContribFeatureHAAR_Params_propRectSize_const_Size(cv::detail::TrackerContribFeatureHAAR::Params* instance, const cv::Size* val) {
		instance->rectSize = *val;
}

bool cv_detail_TrackerContribFeatureHAAR_Params_propIsIntegral_const(const cv::detail::TrackerContribFeatureHAAR::Params* instance) {
		bool ret = instance->isIntegral;
		return ret;
}

void cv_detail_TrackerContribFeatureHAAR_Params_propIsIntegral_const_bool(cv::detail::TrackerContribFeatureHAAR::Params* instance, const bool val) {
		instance->isIntegral = val;
}

void cv_detail_TrackerContribFeatureHAAR_Params_delete(cv::detail::TrackerContribFeatureHAAR::Params* instance) {
		delete instance;
}

void cv_detail_TrackerContribFeatureSet_TrackerContribFeatureSet(Result<cv::detail::TrackerContribFeatureSet*>* ocvrs_return) {
	try {
		cv::detail::TrackerContribFeatureSet* ret = new cv::detail::TrackerContribFeatureSet();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureSet_extraction_const_vectorLMatGR(cv::detail::TrackerContribFeatureSet* instance, const std::vector<cv::Mat>* images, ResultVoid* ocvrs_return) {
	try {
		instance->extraction(*images);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureSet_selection(cv::detail::TrackerContribFeatureSet* instance, ResultVoid* ocvrs_return) {
	try {
		instance->selection();
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureSet_removeOutliers(cv::detail::TrackerContribFeatureSet* instance, ResultVoid* ocvrs_return) {
	try {
		instance->removeOutliers();
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureSet_addTrackerFeature_String(cv::detail::TrackerContribFeatureSet* instance, const char* trackerFeatureType, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->addTrackerFeature(std::string(trackerFeatureType));
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureSet_addTrackerFeature_PtrLTrackerContribFeatureGR(cv::detail::TrackerContribFeatureSet* instance, cv::Ptr<cv::detail::TrackerContribFeature>* feature, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->addTrackerFeature(*feature);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureSet_getTrackerFeature_const(const cv::detail::TrackerContribFeatureSet* instance, Result<std::vector<std::pair<cv::String, cv::Ptr<cv::detail::TrackerContribFeature>>>*>* ocvrs_return) {
	try {
		const std::vector<std::pair<cv::String, cv::Ptr<cv::detail::TrackerContribFeature>>> ret = instance->getTrackerFeature();
		Ok(new const std::vector<std::pair<cv::String, cv::Ptr<cv::detail::TrackerContribFeature>>>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureSet_getResponses_const(const cv::detail::TrackerContribFeatureSet* instance, Result<std::vector<cv::Mat>*>* ocvrs_return) {
	try {
		const std::vector<cv::Mat> ret = instance->getResponses();
		Ok(new const std::vector<cv::Mat>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribFeatureSet_delete(cv::detail::TrackerContribFeatureSet* instance) {
		delete instance;
}

void cv_detail_TrackerContribSampler_TrackerContribSampler(Result<cv::detail::TrackerContribSampler*>* ocvrs_return) {
	try {
		cv::detail::TrackerContribSampler* ret = new cv::detail::TrackerContribSampler();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSampler_sampling_const_MatR_Rect(cv::detail::TrackerContribSampler* instance, const cv::Mat* image, cv::Rect* boundingBox, ResultVoid* ocvrs_return) {
	try {
		instance->sampling(*image, *boundingBox);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSampler_getSamplers_const(const cv::detail::TrackerContribSampler* instance, Result<std::vector<std::pair<cv::String, cv::Ptr<cv::detail::TrackerContribSamplerAlgorithm>>>*>* ocvrs_return) {
	try {
		const std::vector<std::pair<cv::String, cv::Ptr<cv::detail::TrackerContribSamplerAlgorithm>>> ret = instance->getSamplers();
		Ok(new const std::vector<std::pair<cv::String, cv::Ptr<cv::detail::TrackerContribSamplerAlgorithm>>>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSampler_getSamples_const(const cv::detail::TrackerContribSampler* instance, Result<std::vector<cv::Mat>*>* ocvrs_return) {
	try {
		const std::vector<cv::Mat> ret = instance->getSamples();
		Ok(new const std::vector<cv::Mat>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSampler_addTrackerSamplerAlgorithm_String(cv::detail::TrackerContribSampler* instance, const char* trackerSamplerAlgorithmType, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->addTrackerSamplerAlgorithm(std::string(trackerSamplerAlgorithmType));
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSampler_addTrackerSamplerAlgorithm_PtrLTrackerContribSamplerAlgorithmGR(cv::detail::TrackerContribSampler* instance, cv::Ptr<cv::detail::TrackerContribSamplerAlgorithm>* sampler, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->addTrackerSamplerAlgorithm(*sampler);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSampler_delete(cv::detail::TrackerContribSampler* instance) {
		delete instance;
}

void cv_detail_TrackerContribSamplerAlgorithm_create_const_StringR(const char* trackerSamplerType, Result<cv::Ptr<cv::detail::TrackerContribSamplerAlgorithm>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::detail::TrackerContribSamplerAlgorithm> ret = cv::detail::TrackerContribSamplerAlgorithm::create(std::string(trackerSamplerType));
		Ok(new cv::Ptr<cv::detail::TrackerContribSamplerAlgorithm>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSamplerAlgorithm_sampling_const_MatR_const_RectR_vectorLMatGR(cv::detail::TrackerContribSamplerAlgorithm* instance, const cv::Mat* image, const cv::Rect* boundingBox, std::vector<cv::Mat>* sample, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->sampling(*image, *boundingBox, *sample);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSamplerAlgorithm_getClassName_const(const cv::detail::TrackerContribSamplerAlgorithm* instance, Result<void*>* ocvrs_return) {
	try {
		cv::String ret = instance->getClassName();
		Ok(ocvrs_create_string(ret.c_str()), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribSamplerCSC* cv_detail_TrackerContribSamplerAlgorithm_to_Detail_TrackerContribSamplerCSC(cv::detail::TrackerContribSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerContribSamplerCSC*>(instance);
}

cv::detail::TrackerSamplerCS* cv_detail_TrackerContribSamplerAlgorithm_to_Detail_TrackerSamplerCS(cv::detail::TrackerContribSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerCS*>(instance);
}

cv::detail::TrackerSamplerPF* cv_detail_TrackerContribSamplerAlgorithm_to_Detail_TrackerSamplerPF(cv::detail::TrackerContribSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerPF*>(instance);
}

cv::detail::TrackerSamplerAlgorithm* cv_detail_TrackerContribSamplerAlgorithm_to_Detail_TrackerSamplerAlgorithm(cv::detail::TrackerContribSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerAlgorithm*>(instance);
}

void cv_detail_TrackerContribSamplerAlgorithm_delete(cv::detail::TrackerContribSamplerAlgorithm* instance) {
		delete instance;
}

void cv_detail_TrackerContribSamplerCSC_TrackerContribSamplerCSC_const_ParamsR(const cv::detail::TrackerContribSamplerCSC::Params* parameters, Result<cv::detail::TrackerContribSamplerCSC*>* ocvrs_return) {
	try {
		cv::detail::TrackerContribSamplerCSC* ret = new cv::detail::TrackerContribSamplerCSC(*parameters);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSamplerCSC_TrackerContribSamplerCSC(Result<cv::detail::TrackerContribSamplerCSC*>* ocvrs_return) {
	try {
		cv::detail::TrackerContribSamplerCSC* ret = new cv::detail::TrackerContribSamplerCSC();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerContribSamplerCSC_setMode_int(cv::detail::TrackerContribSamplerCSC* instance, int samplingMode, ResultVoid* ocvrs_return) {
	try {
		instance->setMode(samplingMode);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribSamplerAlgorithm* cv_detail_TrackerContribSamplerCSC_to_Detail_TrackerContribSamplerAlgorithm(cv::detail::TrackerContribSamplerCSC* instance) {
		return dynamic_cast<cv::detail::TrackerContribSamplerAlgorithm*>(instance);
}

cv::detail::TrackerSamplerAlgorithm* cv_detail_TrackerContribSamplerCSC_to_Detail_TrackerSamplerAlgorithm(cv::detail::TrackerContribSamplerCSC* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerAlgorithm*>(instance);
}

void cv_detail_TrackerContribSamplerCSC_delete(cv::detail::TrackerContribSamplerCSC* instance) {
		delete instance;
}

void cv_detail_TrackerContribSamplerCSC_Params_Params(Result<cv::detail::TrackerContribSamplerCSC::Params*>* ocvrs_return) {
	try {
		cv::detail::TrackerContribSamplerCSC::Params* ret = new cv::detail::TrackerContribSamplerCSC::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

float cv_detail_TrackerContribSamplerCSC_Params_propInitInRad_const(const cv::detail::TrackerContribSamplerCSC::Params* instance) {
		float ret = instance->initInRad;
		return ret;
}

void cv_detail_TrackerContribSamplerCSC_Params_propInitInRad_const_float(cv::detail::TrackerContribSamplerCSC::Params* instance, const float val) {
		instance->initInRad = val;
}

float cv_detail_TrackerContribSamplerCSC_Params_propTrackInPosRad_const(const cv::detail::TrackerContribSamplerCSC::Params* instance) {
		float ret = instance->trackInPosRad;
		return ret;
}

void cv_detail_TrackerContribSamplerCSC_Params_propTrackInPosRad_const_float(cv::detail::TrackerContribSamplerCSC::Params* instance, const float val) {
		instance->trackInPosRad = val;
}

float cv_detail_TrackerContribSamplerCSC_Params_propSearchWinSize_const(const cv::detail::TrackerContribSamplerCSC::Params* instance) {
		float ret = instance->searchWinSize;
		return ret;
}

void cv_detail_TrackerContribSamplerCSC_Params_propSearchWinSize_const_float(cv::detail::TrackerContribSamplerCSC::Params* instance, const float val) {
		instance->searchWinSize = val;
}

int cv_detail_TrackerContribSamplerCSC_Params_propInitMaxNegNum_const(const cv::detail::TrackerContribSamplerCSC::Params* instance) {
		int ret = instance->initMaxNegNum;
		return ret;
}

void cv_detail_TrackerContribSamplerCSC_Params_propInitMaxNegNum_const_int(cv::detail::TrackerContribSamplerCSC::Params* instance, const int val) {
		instance->initMaxNegNum = val;
}

int cv_detail_TrackerContribSamplerCSC_Params_propTrackMaxPosNum_const(const cv::detail::TrackerContribSamplerCSC::Params* instance) {
		int ret = instance->trackMaxPosNum;
		return ret;
}

void cv_detail_TrackerContribSamplerCSC_Params_propTrackMaxPosNum_const_int(cv::detail::TrackerContribSamplerCSC::Params* instance, const int val) {
		instance->trackMaxPosNum = val;
}

int cv_detail_TrackerContribSamplerCSC_Params_propTrackMaxNegNum_const(const cv::detail::TrackerContribSamplerCSC::Params* instance) {
		int ret = instance->trackMaxNegNum;
		return ret;
}

void cv_detail_TrackerContribSamplerCSC_Params_propTrackMaxNegNum_const_int(cv::detail::TrackerContribSamplerCSC::Params* instance, const int val) {
		instance->trackMaxNegNum = val;
}

void cv_detail_TrackerContribSamplerCSC_Params_delete(cv::detail::TrackerContribSamplerCSC::Params* instance) {
		delete instance;
}

void cv_detail_TrackerFeature_compute_const_vectorLMatGR_MatR(cv::detail::TrackerFeature* instance, const std::vector<cv::Mat>* images, cv::Mat* response, ResultVoid* ocvrs_return) {
	try {
		instance->compute(*images, *response);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribFeature* cv_detail_TrackerFeature_to_Detail_TrackerContribFeature(cv::detail::TrackerFeature* instance) {
		return dynamic_cast<cv::detail::TrackerContribFeature*>(instance);
}

cv::detail::TrackerContribFeatureHAAR* cv_detail_TrackerFeature_to_Detail_TrackerContribFeatureHAAR(cv::detail::TrackerFeature* instance) {
		return dynamic_cast<cv::detail::TrackerContribFeatureHAAR*>(instance);
}

cv::detail::TrackerFeatureFeature2d* cv_detail_TrackerFeature_to_Detail_TrackerFeatureFeature2d(cv::detail::TrackerFeature* instance) {
		return dynamic_cast<cv::detail::TrackerFeatureFeature2d*>(instance);
}

cv::detail::TrackerFeatureHOG* cv_detail_TrackerFeature_to_Detail_TrackerFeatureHOG(cv::detail::TrackerFeature* instance) {
		return dynamic_cast<cv::detail::TrackerFeatureHOG*>(instance);
}

cv::detail::TrackerFeatureLBP* cv_detail_TrackerFeature_to_Detail_TrackerFeatureLBP(cv::detail::TrackerFeature* instance) {
		return dynamic_cast<cv::detail::TrackerFeatureLBP*>(instance);
}

void cv_detail_TrackerFeature_delete(cv::detail::TrackerFeature* instance) {
		delete instance;
}

void cv_detail_TrackerFeatureFeature2d_TrackerFeatureFeature2d_String_String(const char* detectorType, const char* descriptorType, Result<cv::detail::TrackerFeatureFeature2d*>* ocvrs_return) {
	try {
		cv::detail::TrackerFeatureFeature2d* ret = new cv::detail::TrackerFeatureFeature2d(std::string(detectorType), std::string(descriptorType));
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerFeatureFeature2d_selection_MatR_int(cv::detail::TrackerFeatureFeature2d* instance, cv::Mat* response, int npoints, ResultVoid* ocvrs_return) {
	try {
		instance->selection(*response, npoints);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribFeature* cv_detail_TrackerFeatureFeature2d_to_Detail_TrackerContribFeature(cv::detail::TrackerFeatureFeature2d* instance) {
		return dynamic_cast<cv::detail::TrackerContribFeature*>(instance);
}

cv::detail::TrackerFeature* cv_detail_TrackerFeatureFeature2d_to_Detail_TrackerFeature(cv::detail::TrackerFeatureFeature2d* instance) {
		return dynamic_cast<cv::detail::TrackerFeature*>(instance);
}

void cv_detail_TrackerFeatureFeature2d_delete(cv::detail::TrackerFeatureFeature2d* instance) {
		delete instance;
}

void cv_detail_TrackerFeatureHOG_TrackerFeatureHOG(Result<cv::detail::TrackerFeatureHOG*>* ocvrs_return) {
	try {
		cv::detail::TrackerFeatureHOG* ret = new cv::detail::TrackerFeatureHOG();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerFeatureHOG_selection_MatR_int(cv::detail::TrackerFeatureHOG* instance, cv::Mat* response, int npoints, ResultVoid* ocvrs_return) {
	try {
		instance->selection(*response, npoints);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribFeature* cv_detail_TrackerFeatureHOG_to_Detail_TrackerContribFeature(cv::detail::TrackerFeatureHOG* instance) {
		return dynamic_cast<cv::detail::TrackerContribFeature*>(instance);
}

cv::detail::TrackerFeature* cv_detail_TrackerFeatureHOG_to_Detail_TrackerFeature(cv::detail::TrackerFeatureHOG* instance) {
		return dynamic_cast<cv::detail::TrackerFeature*>(instance);
}

void cv_detail_TrackerFeatureHOG_delete(cv::detail::TrackerFeatureHOG* instance) {
		delete instance;
}

void cv_detail_TrackerFeatureLBP_TrackerFeatureLBP(Result<cv::detail::TrackerFeatureLBP*>* ocvrs_return) {
	try {
		cv::detail::TrackerFeatureLBP* ret = new cv::detail::TrackerFeatureLBP();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerFeatureLBP_selection_MatR_int(cv::detail::TrackerFeatureLBP* instance, cv::Mat* response, int npoints, ResultVoid* ocvrs_return) {
	try {
		instance->selection(*response, npoints);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribFeature* cv_detail_TrackerFeatureLBP_to_Detail_TrackerContribFeature(cv::detail::TrackerFeatureLBP* instance) {
		return dynamic_cast<cv::detail::TrackerContribFeature*>(instance);
}

cv::detail::TrackerFeature* cv_detail_TrackerFeatureLBP_to_Detail_TrackerFeature(cv::detail::TrackerFeatureLBP* instance) {
		return dynamic_cast<cv::detail::TrackerFeature*>(instance);
}

void cv_detail_TrackerFeatureLBP_delete(cv::detail::TrackerFeatureLBP* instance) {
		delete instance;
}

void cv_detail_TrackerFeatureSet_TrackerFeatureSet(Result<cv::detail::TrackerFeatureSet*>* ocvrs_return) {
	try {
		cv::detail::TrackerFeatureSet* ret = new cv::detail::TrackerFeatureSet();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerFeatureSet_extraction_const_vectorLMatGR(cv::detail::TrackerFeatureSet* instance, const std::vector<cv::Mat>* images, ResultVoid* ocvrs_return) {
	try {
		instance->extraction(*images);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerFeatureSet_addTrackerFeature_const_PtrLTrackerFeatureGR(cv::detail::TrackerFeatureSet* instance, const cv::Ptr<cv::detail::TrackerFeature>* feature, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->addTrackerFeature(*feature);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerFeatureSet_getTrackerFeatures_const(const cv::detail::TrackerFeatureSet* instance, Result<std::vector<cv::Ptr<cv::detail::TrackerFeature>>*>* ocvrs_return) {
	try {
		const std::vector<cv::Ptr<cv::detail::TrackerFeature>> ret = instance->getTrackerFeatures();
		Ok(new const std::vector<cv::Ptr<cv::detail::TrackerFeature>>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerFeatureSet_getResponses_const(const cv::detail::TrackerFeatureSet* instance, Result<std::vector<cv::Mat>*>* ocvrs_return) {
	try {
		const std::vector<cv::Mat> ret = instance->getResponses();
		Ok(new const std::vector<cv::Mat>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerFeatureSet_delete(cv::detail::TrackerFeatureSet* instance) {
		delete instance;
}

void cv_detail_TrackerModel_setTrackerStateEstimator_PtrLTrackerStateEstimatorG(cv::detail::TrackerModel* instance, cv::Ptr<cv::detail::TrackerStateEstimator>* trackerStateEstimator, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->setTrackerStateEstimator(*trackerStateEstimator);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_modelEstimation_const_vectorLMatGR(cv::detail::TrackerModel* instance, const std::vector<cv::Mat>* responses, ResultVoid* ocvrs_return) {
	try {
		instance->modelEstimation(*responses);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_modelUpdate(cv::detail::TrackerModel* instance, ResultVoid* ocvrs_return) {
	try {
		instance->modelUpdate();
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_runStateEstimator(cv::detail::TrackerModel* instance, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->runStateEstimator();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_setLastTargetState_const_PtrLTrackerTargetStateGR(cv::detail::TrackerModel* instance, const cv::Ptr<cv::detail::TrackerTargetState>* lastTargetState, ResultVoid* ocvrs_return) {
	try {
		instance->setLastTargetState(*lastTargetState);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_getLastTargetState_const(const cv::detail::TrackerModel* instance, Result<cv::Ptr<cv::detail::TrackerTargetState>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::detail::TrackerTargetState> ret = instance->getLastTargetState();
		Ok(new cv::Ptr<cv::detail::TrackerTargetState>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_getConfidenceMaps_const(const cv::detail::TrackerModel* instance, Result<std::vector<cv::detail::ConfidenceMap>*>* ocvrs_return) {
	try {
		const std::vector<cv::detail::ConfidenceMap> ret = instance->getConfidenceMaps();
		Ok(new const std::vector<cv::detail::ConfidenceMap>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_getLastConfidenceMap_const(const cv::detail::TrackerModel* instance, Result<cv::detail::ConfidenceMap*>* ocvrs_return) {
	try {
		const cv::detail::ConfidenceMap ret = instance->getLastConfidenceMap();
		Ok(new const cv::detail::ConfidenceMap(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_getTrackerStateEstimator_const(const cv::detail::TrackerModel* instance, Result<cv::Ptr<cv::detail::TrackerStateEstimator>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::detail::TrackerStateEstimator> ret = instance->getTrackerStateEstimator();
		Ok(new cv::Ptr<cv::detail::TrackerStateEstimator>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerModel_delete(cv::detail::TrackerModel* instance) {
		delete instance;
}

void cv_detail_TrackerSampler_TrackerSampler(Result<cv::detail::TrackerSampler*>* ocvrs_return) {
	try {
		cv::detail::TrackerSampler* ret = new cv::detail::TrackerSampler();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSampler_sampling_const_MatR_Rect(cv::detail::TrackerSampler* instance, const cv::Mat* image, cv::Rect* boundingBox, ResultVoid* ocvrs_return) {
	try {
		instance->sampling(*image, *boundingBox);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSampler_getSamplers_const(const cv::detail::TrackerSampler* instance, Result<std::vector<cv::Ptr<cv::detail::TrackerSamplerAlgorithm>>*>* ocvrs_return) {
	try {
		const std::vector<cv::Ptr<cv::detail::TrackerSamplerAlgorithm>> ret = instance->getSamplers();
		Ok(new const std::vector<cv::Ptr<cv::detail::TrackerSamplerAlgorithm>>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSampler_getSamples_const(const cv::detail::TrackerSampler* instance, Result<std::vector<cv::Mat>*>* ocvrs_return) {
	try {
		const std::vector<cv::Mat> ret = instance->getSamples();
		Ok(new const std::vector<cv::Mat>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSampler_addTrackerSamplerAlgorithm_const_PtrLTrackerSamplerAlgorithmGR(cv::detail::TrackerSampler* instance, const cv::Ptr<cv::detail::TrackerSamplerAlgorithm>* sampler, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->addTrackerSamplerAlgorithm(*sampler);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSampler_delete(cv::detail::TrackerSampler* instance) {
		delete instance;
}

void cv_detail_TrackerSamplerAlgorithm_sampling_const_MatR_const_RectR_vectorLMatGR(cv::detail::TrackerSamplerAlgorithm* instance, const cv::Mat* image, const cv::Rect* boundingBox, std::vector<cv::Mat>* sample, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->sampling(*image, *boundingBox, *sample);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribSamplerAlgorithm* cv_detail_TrackerSamplerAlgorithm_to_Detail_TrackerContribSamplerAlgorithm(cv::detail::TrackerSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerContribSamplerAlgorithm*>(instance);
}

cv::detail::TrackerContribSamplerCSC* cv_detail_TrackerSamplerAlgorithm_to_Detail_TrackerContribSamplerCSC(cv::detail::TrackerSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerContribSamplerCSC*>(instance);
}

cv::detail::TrackerSamplerCS* cv_detail_TrackerSamplerAlgorithm_to_Detail_TrackerSamplerCS(cv::detail::TrackerSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerCS*>(instance);
}

cv::detail::TrackerSamplerCSC* cv_detail_TrackerSamplerAlgorithm_to_Detail_TrackerSamplerCSC(cv::detail::TrackerSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerCSC*>(instance);
}

cv::detail::TrackerSamplerPF* cv_detail_TrackerSamplerAlgorithm_to_Detail_TrackerSamplerPF(cv::detail::TrackerSamplerAlgorithm* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerPF*>(instance);
}

void cv_detail_TrackerSamplerAlgorithm_delete(cv::detail::TrackerSamplerAlgorithm* instance) {
		delete instance;
}

void cv_detail_TrackerSamplerCS_TrackerSamplerCS_const_ParamsR(const cv::detail::TrackerSamplerCS::Params* parameters, Result<cv::detail::TrackerSamplerCS*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerCS* ret = new cv::detail::TrackerSamplerCS(*parameters);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSamplerCS_TrackerSamplerCS(Result<cv::detail::TrackerSamplerCS*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerCS* ret = new cv::detail::TrackerSamplerCS();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSamplerCS_setMode_int(cv::detail::TrackerSamplerCS* instance, int samplingMode, ResultVoid* ocvrs_return) {
	try {
		instance->setMode(samplingMode);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSamplerCS_samplingImpl_const_MatR_Rect_vectorLMatGR(cv::detail::TrackerSamplerCS* instance, const cv::Mat* image, cv::Rect* boundingBox, std::vector<cv::Mat>* sample, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->samplingImpl(*image, *boundingBox, *sample);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSamplerCS_getROI_const(const cv::detail::TrackerSamplerCS* instance, Result<cv::Rect>* ocvrs_return) {
	try {
		cv::Rect ret = instance->getROI();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribSamplerAlgorithm* cv_detail_TrackerSamplerCS_to_Detail_TrackerContribSamplerAlgorithm(cv::detail::TrackerSamplerCS* instance) {
		return dynamic_cast<cv::detail::TrackerContribSamplerAlgorithm*>(instance);
}

cv::detail::TrackerSamplerAlgorithm* cv_detail_TrackerSamplerCS_to_Detail_TrackerSamplerAlgorithm(cv::detail::TrackerSamplerCS* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerAlgorithm*>(instance);
}

void cv_detail_TrackerSamplerCS_delete(cv::detail::TrackerSamplerCS* instance) {
		delete instance;
}

void cv_detail_TrackerSamplerCS_Params_Params(Result<cv::detail::TrackerSamplerCS::Params*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerCS::Params* ret = new cv::detail::TrackerSamplerCS::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

float cv_detail_TrackerSamplerCS_Params_propOverlap_const(const cv::detail::TrackerSamplerCS::Params* instance) {
		float ret = instance->overlap;
		return ret;
}

void cv_detail_TrackerSamplerCS_Params_propOverlap_const_float(cv::detail::TrackerSamplerCS::Params* instance, const float val) {
		instance->overlap = val;
}

float cv_detail_TrackerSamplerCS_Params_propSearchFactor_const(const cv::detail::TrackerSamplerCS::Params* instance) {
		float ret = instance->searchFactor;
		return ret;
}

void cv_detail_TrackerSamplerCS_Params_propSearchFactor_const_float(cv::detail::TrackerSamplerCS::Params* instance, const float val) {
		instance->searchFactor = val;
}

void cv_detail_TrackerSamplerCS_Params_delete(cv::detail::TrackerSamplerCS::Params* instance) {
		delete instance;
}

void cv_detail_TrackerSamplerCSC_TrackerSamplerCSC_const_ParamsR(const cv::detail::TrackerSamplerCSC::Params* parameters, Result<cv::detail::TrackerSamplerCSC*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerCSC* ret = new cv::detail::TrackerSamplerCSC(*parameters);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSamplerCSC_TrackerSamplerCSC(Result<cv::detail::TrackerSamplerCSC*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerCSC* ret = new cv::detail::TrackerSamplerCSC();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSamplerCSC_setMode_int(cv::detail::TrackerSamplerCSC* instance, int samplingMode, ResultVoid* ocvrs_return) {
	try {
		instance->setMode(samplingMode);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSamplerCSC_sampling_const_MatR_const_RectR_vectorLMatGR(cv::detail::TrackerSamplerCSC* instance, const cv::Mat* image, const cv::Rect* boundingBox, std::vector<cv::Mat>* sample, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->sampling(*image, *boundingBox, *sample);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerSamplerAlgorithm* cv_detail_TrackerSamplerCSC_to_Detail_TrackerSamplerAlgorithm(cv::detail::TrackerSamplerCSC* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerAlgorithm*>(instance);
}

void cv_detail_TrackerSamplerCSC_delete(cv::detail::TrackerSamplerCSC* instance) {
		delete instance;
}

void cv_detail_TrackerSamplerCSC_Params_Params(Result<cv::detail::TrackerSamplerCSC::Params*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerCSC::Params* ret = new cv::detail::TrackerSamplerCSC::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

float cv_detail_TrackerSamplerCSC_Params_propInitInRad_const(const cv::detail::TrackerSamplerCSC::Params* instance) {
		float ret = instance->initInRad;
		return ret;
}

void cv_detail_TrackerSamplerCSC_Params_propInitInRad_const_float(cv::detail::TrackerSamplerCSC::Params* instance, const float val) {
		instance->initInRad = val;
}

float cv_detail_TrackerSamplerCSC_Params_propTrackInPosRad_const(const cv::detail::TrackerSamplerCSC::Params* instance) {
		float ret = instance->trackInPosRad;
		return ret;
}

void cv_detail_TrackerSamplerCSC_Params_propTrackInPosRad_const_float(cv::detail::TrackerSamplerCSC::Params* instance, const float val) {
		instance->trackInPosRad = val;
}

float cv_detail_TrackerSamplerCSC_Params_propSearchWinSize_const(const cv::detail::TrackerSamplerCSC::Params* instance) {
		float ret = instance->searchWinSize;
		return ret;
}

void cv_detail_TrackerSamplerCSC_Params_propSearchWinSize_const_float(cv::detail::TrackerSamplerCSC::Params* instance, const float val) {
		instance->searchWinSize = val;
}

int cv_detail_TrackerSamplerCSC_Params_propInitMaxNegNum_const(const cv::detail::TrackerSamplerCSC::Params* instance) {
		int ret = instance->initMaxNegNum;
		return ret;
}

void cv_detail_TrackerSamplerCSC_Params_propInitMaxNegNum_const_int(cv::detail::TrackerSamplerCSC::Params* instance, const int val) {
		instance->initMaxNegNum = val;
}

int cv_detail_TrackerSamplerCSC_Params_propTrackMaxPosNum_const(const cv::detail::TrackerSamplerCSC::Params* instance) {
		int ret = instance->trackMaxPosNum;
		return ret;
}

void cv_detail_TrackerSamplerCSC_Params_propTrackMaxPosNum_const_int(cv::detail::TrackerSamplerCSC::Params* instance, const int val) {
		instance->trackMaxPosNum = val;
}

int cv_detail_TrackerSamplerCSC_Params_propTrackMaxNegNum_const(const cv::detail::TrackerSamplerCSC::Params* instance) {
		int ret = instance->trackMaxNegNum;
		return ret;
}

void cv_detail_TrackerSamplerCSC_Params_propTrackMaxNegNum_const_int(cv::detail::TrackerSamplerCSC::Params* instance, const int val) {
		instance->trackMaxNegNum = val;
}

void cv_detail_TrackerSamplerCSC_Params_delete(cv::detail::TrackerSamplerCSC::Params* instance) {
		delete instance;
}

void cv_detail_TrackerSamplerPF_TrackerSamplerPF_const_MatR_const_ParamsR(const cv::Mat* chosenRect, const cv::detail::TrackerSamplerPF::Params* parameters, Result<cv::detail::TrackerSamplerPF*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerPF* ret = new cv::detail::TrackerSamplerPF(*chosenRect, *parameters);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerSamplerPF_TrackerSamplerPF_const_MatR(const cv::Mat* chosenRect, Result<cv::detail::TrackerSamplerPF*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerPF* ret = new cv::detail::TrackerSamplerPF(*chosenRect);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerContribSamplerAlgorithm* cv_detail_TrackerSamplerPF_to_Detail_TrackerContribSamplerAlgorithm(cv::detail::TrackerSamplerPF* instance) {
		return dynamic_cast<cv::detail::TrackerContribSamplerAlgorithm*>(instance);
}

cv::detail::TrackerSamplerAlgorithm* cv_detail_TrackerSamplerPF_to_Detail_TrackerSamplerAlgorithm(cv::detail::TrackerSamplerPF* instance) {
		return dynamic_cast<cv::detail::TrackerSamplerAlgorithm*>(instance);
}

void cv_detail_TrackerSamplerPF_delete(cv::detail::TrackerSamplerPF* instance) {
		delete instance;
}

void cv_detail_TrackerSamplerPF_Params_Params(Result<cv::detail::TrackerSamplerPF::Params*>* ocvrs_return) {
	try {
		cv::detail::TrackerSamplerPF::Params* ret = new cv::detail::TrackerSamplerPF::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

int cv_detail_TrackerSamplerPF_Params_propIterationNum_const(const cv::detail::TrackerSamplerPF::Params* instance) {
		int ret = instance->iterationNum;
		return ret;
}

void cv_detail_TrackerSamplerPF_Params_propIterationNum_const_int(cv::detail::TrackerSamplerPF::Params* instance, const int val) {
		instance->iterationNum = val;
}

int cv_detail_TrackerSamplerPF_Params_propParticlesNum_const(const cv::detail::TrackerSamplerPF::Params* instance) {
		int ret = instance->particlesNum;
		return ret;
}

void cv_detail_TrackerSamplerPF_Params_propParticlesNum_const_int(cv::detail::TrackerSamplerPF::Params* instance, const int val) {
		instance->particlesNum = val;
}

double cv_detail_TrackerSamplerPF_Params_propAlpha_const(const cv::detail::TrackerSamplerPF::Params* instance) {
		double ret = instance->alpha;
		return ret;
}

void cv_detail_TrackerSamplerPF_Params_propAlpha_const_double(cv::detail::TrackerSamplerPF::Params* instance, const double val) {
		instance->alpha = val;
}

cv::Mat_<double>* cv_detail_TrackerSamplerPF_Params_propStd_const(const cv::detail::TrackerSamplerPF::Params* instance) {
		cv::Mat_<double> ret = instance->std;
		return new cv::Mat_<double>(ret);
}

void cv_detail_TrackerSamplerPF_Params_propStd_const_Mat_LdoubleG(cv::detail::TrackerSamplerPF::Params* instance, const cv::Mat_<double>* val) {
		instance->std = *val;
}

void cv_detail_TrackerSamplerPF_Params_delete(cv::detail::TrackerSamplerPF::Params* instance) {
		delete instance;
}

void cv_detail_TrackerStateEstimator_estimate_const_vectorLConfidenceMapGR(cv::detail::TrackerStateEstimator* instance, const std::vector<cv::detail::ConfidenceMap>* confidenceMaps, Result<cv::Ptr<cv::detail::TrackerTargetState>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::detail::TrackerTargetState> ret = instance->estimate(*confidenceMaps);
		Ok(new cv::Ptr<cv::detail::TrackerTargetState>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimator_update_vectorLConfidenceMapGR(cv::detail::TrackerStateEstimator* instance, std::vector<cv::detail::ConfidenceMap>* confidenceMaps, ResultVoid* ocvrs_return) {
	try {
		instance->update(*confidenceMaps);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimator_create_const_StringR(const char* trackeStateEstimatorType, Result<cv::Ptr<cv::detail::TrackerStateEstimator>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::detail::TrackerStateEstimator> ret = cv::detail::TrackerStateEstimator::create(std::string(trackeStateEstimatorType));
		Ok(new cv::Ptr<cv::detail::TrackerStateEstimator>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimator_getClassName_const(const cv::detail::TrackerStateEstimator* instance, Result<void*>* ocvrs_return) {
	try {
		cv::String ret = instance->getClassName();
		Ok(ocvrs_create_string(ret.c_str()), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerStateEstimatorAdaBoosting* cv_detail_TrackerStateEstimator_to_Detail_TrackerStateEstimatorAdaBoosting(cv::detail::TrackerStateEstimator* instance) {
		return dynamic_cast<cv::detail::TrackerStateEstimatorAdaBoosting*>(instance);
}

cv::detail::TrackerStateEstimatorSVM* cv_detail_TrackerStateEstimator_to_Detail_TrackerStateEstimatorSVM(cv::detail::TrackerStateEstimator* instance) {
		return dynamic_cast<cv::detail::TrackerStateEstimatorSVM*>(instance);
}

void cv_detail_TrackerStateEstimator_delete(cv::detail::TrackerStateEstimator* instance) {
		delete instance;
}

void cv_detail_TrackerStateEstimatorAdaBoosting_TrackerStateEstimatorAdaBoosting_int_int_int_Size_const_RectR(int numClassifer, int initIterations, int nFeatures, cv::Size* patchSize, const cv::Rect* ROI, Result<cv::detail::TrackerStateEstimatorAdaBoosting*>* ocvrs_return) {
	try {
		cv::detail::TrackerStateEstimatorAdaBoosting* ret = new cv::detail::TrackerStateEstimatorAdaBoosting(numClassifer, initIterations, nFeatures, *patchSize, *ROI);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_getSampleROI_const(const cv::detail::TrackerStateEstimatorAdaBoosting* instance, Result<cv::Rect>* ocvrs_return) {
	try {
		cv::Rect ret = instance->getSampleROI();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_setSampleROI_const_RectR(cv::detail::TrackerStateEstimatorAdaBoosting* instance, const cv::Rect* ROI, ResultVoid* ocvrs_return) {
	try {
		instance->setSampleROI(*ROI);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_setCurrentConfidenceMap_ConfidenceMapR(cv::detail::TrackerStateEstimatorAdaBoosting* instance, cv::detail::ConfidenceMap* confidenceMap, ResultVoid* ocvrs_return) {
	try {
		instance->setCurrentConfidenceMap(*confidenceMap);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_computeSelectedWeakClassifier(cv::detail::TrackerStateEstimatorAdaBoosting* instance, Result<std::vector<int>*>* ocvrs_return) {
	try {
		std::vector<int> ret = instance->computeSelectedWeakClassifier();
		Ok(new std::vector<int>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_computeReplacedClassifier(cv::detail::TrackerStateEstimatorAdaBoosting* instance, Result<std::vector<int>*>* ocvrs_return) {
	try {
		std::vector<int> ret = instance->computeReplacedClassifier();
		Ok(new std::vector<int>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_computeSwappedClassifier(cv::detail::TrackerStateEstimatorAdaBoosting* instance, Result<std::vector<int>*>* ocvrs_return) {
	try {
		std::vector<int> ret = instance->computeSwappedClassifier();
		Ok(new std::vector<int>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerStateEstimator* cv_detail_TrackerStateEstimatorAdaBoosting_to_Detail_TrackerStateEstimator(cv::detail::TrackerStateEstimatorAdaBoosting* instance) {
		return dynamic_cast<cv::detail::TrackerStateEstimator*>(instance);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_delete(cv::detail::TrackerStateEstimatorAdaBoosting* instance) {
		delete instance;
}

void cv_detail_TrackerStateEstimatorAdaBoosting_TrackerAdaBoostingTargetState_TrackerAdaBoostingTargetState_const_Point2fR_int_int_bool_const_MatR(const cv::Point2f* position, int width, int height, bool foreground, const cv::Mat* responses, Result<cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState*>* ocvrs_return) {
	try {
		cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState* ret = new cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState(*position, width, height, foreground, *responses);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_TrackerAdaBoostingTargetState_setTargetResponses_const_MatR(cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState* instance, const cv::Mat* responses, ResultVoid* ocvrs_return) {
	try {
		instance->setTargetResponses(*responses);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_TrackerAdaBoostingTargetState_setTargetFg_bool(cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState* instance, bool foreground, ResultVoid* ocvrs_return) {
	try {
		instance->setTargetFg(foreground);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_TrackerAdaBoostingTargetState_getTargetResponses_const(const cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState* instance, Result<cv::Mat*>* ocvrs_return) {
	try {
		cv::Mat ret = instance->getTargetResponses();
		Ok(new cv::Mat(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_TrackerAdaBoostingTargetState_isTargetFg_const(const cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState* instance, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->isTargetFg();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerTargetState* cv_detail_TrackerStateEstimatorAdaBoosting_TrackerAdaBoostingTargetState_to_Detail_TrackerTargetState(cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState* instance) {
		return dynamic_cast<cv::detail::TrackerTargetState*>(instance);
}

void cv_detail_TrackerStateEstimatorAdaBoosting_TrackerAdaBoostingTargetState_delete(cv::detail::TrackerStateEstimatorAdaBoosting::TrackerAdaBoostingTargetState* instance) {
		delete instance;
}

void cv_detail_TrackerStateEstimatorSVM_TrackerStateEstimatorSVM(Result<cv::detail::TrackerStateEstimatorSVM*>* ocvrs_return) {
	try {
		cv::detail::TrackerStateEstimatorSVM* ret = new cv::detail::TrackerStateEstimatorSVM();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerStateEstimator* cv_detail_TrackerStateEstimatorSVM_to_Detail_TrackerStateEstimator(cv::detail::TrackerStateEstimatorSVM* instance) {
		return dynamic_cast<cv::detail::TrackerStateEstimator*>(instance);
}

void cv_detail_TrackerStateEstimatorSVM_delete(cv::detail::TrackerStateEstimatorSVM* instance) {
		delete instance;
}

void cv_detail_TrackerTargetState_getTargetPosition_const(const cv::detail::TrackerTargetState* instance, Result<cv::Point2f>* ocvrs_return) {
	try {
		cv::Point2f ret = instance->getTargetPosition();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerTargetState_setTargetPosition_const_Point2fR(cv::detail::TrackerTargetState* instance, const cv::Point2f* position, ResultVoid* ocvrs_return) {
	try {
		instance->setTargetPosition(*position);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerTargetState_getTargetWidth_const(const cv::detail::TrackerTargetState* instance, Result<int>* ocvrs_return) {
	try {
		int ret = instance->getTargetWidth();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerTargetState_setTargetWidth_int(cv::detail::TrackerTargetState* instance, int width, ResultVoid* ocvrs_return) {
	try {
		instance->setTargetWidth(width);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerTargetState_getTargetHeight_const(const cv::detail::TrackerTargetState* instance, Result<int>* ocvrs_return) {
	try {
		int ret = instance->getTargetHeight();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_detail_TrackerTargetState_setTargetHeight_int(cv::detail::TrackerTargetState* instance, int height, ResultVoid* ocvrs_return) {
	try {
		instance->setTargetHeight(height);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::detail::TrackerTargetState* cv_detail_TrackerTargetState_defaultNew_const() {
		cv::detail::TrackerTargetState* ret = new cv::detail::TrackerTargetState();
		return ret;
}

void cv_detail_TrackerTargetState_delete(cv::detail::TrackerTargetState* instance) {
		delete instance;
}

void cv_legacy_MultiTracker_MultiTracker(Result<cv::legacy::MultiTracker*>* ocvrs_return) {
	try {
		cv::legacy::MultiTracker* ret = new cv::legacy::MultiTracker();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_MultiTracker_add_PtrLTrackerG_const__InputArrayR_const_Rect2dR(cv::legacy::MultiTracker* instance, cv::Ptr<cv::legacy::Tracker>* newTracker, const cv::_InputArray* image, const cv::Rect2d* boundingBox, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->add(*newTracker, *image, *boundingBox);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_MultiTracker_add_vectorLPtrLTrackerGG_const__InputArrayR_vectorLRect2dG(cv::legacy::MultiTracker* instance, std::vector<cv::Ptr<cv::legacy::Tracker>>* newTrackers, const cv::_InputArray* image, std::vector<cv::Rect2d>* boundingBox, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->add(*newTrackers, *image, *boundingBox);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_MultiTracker_update_const__InputArrayR(cv::legacy::MultiTracker* instance, const cv::_InputArray* image, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->update(*image);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_MultiTracker_update_const__InputArrayR_vectorLRect2dGR(cv::legacy::MultiTracker* instance, const cv::_InputArray* image, std::vector<cv::Rect2d>* boundingBox, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->update(*image, *boundingBox);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_MultiTracker_getObjects_const(const cv::legacy::MultiTracker* instance, Result<std::vector<cv::Rect2d>*>* ocvrs_return) {
	try {
		const std::vector<cv::Rect2d> ret = instance->getObjects();
		Ok(new const std::vector<cv::Rect2d>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_MultiTracker_create(Result<cv::Ptr<cv::legacy::MultiTracker>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::MultiTracker> ret = cv::legacy::MultiTracker::create();
		Ok(new cv::Ptr<cv::legacy::MultiTracker>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Algorithm* cv_legacy_MultiTracker_to_Algorithm(cv::legacy::MultiTracker* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

void cv_legacy_MultiTracker_delete(cv::legacy::MultiTracker* instance) {
		delete instance;
}

void cv_legacy_MultiTrackerTLD_update_opt_const__InputArrayR(cv::legacy::MultiTrackerTLD* instance, const cv::_InputArray* image, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->update_opt(*image);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::legacy::MultiTrackerTLD* cv_legacy_MultiTrackerTLD_defaultNew_const() {
		cv::legacy::MultiTrackerTLD* ret = new cv::legacy::MultiTrackerTLD();
		return ret;
}

cv::legacy::MultiTracker_Alt* cv_legacy_MultiTrackerTLD_to_Legacy_MultiTracker_Alt(cv::legacy::MultiTrackerTLD* instance) {
		return dynamic_cast<cv::legacy::MultiTracker_Alt*>(instance);
}

void cv_legacy_MultiTrackerTLD_delete(cv::legacy::MultiTrackerTLD* instance) {
		delete instance;
}

void cv_legacy_MultiTracker_Alt_MultiTracker_Alt(Result<cv::legacy::MultiTracker_Alt*>* ocvrs_return) {
	try {
		cv::legacy::MultiTracker_Alt* ret = new cv::legacy::MultiTracker_Alt();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_MultiTracker_Alt_addTarget_const__InputArrayR_const_Rect2dR_PtrLTrackerG(cv::legacy::MultiTracker_Alt* instance, const cv::_InputArray* image, const cv::Rect2d* boundingBox, cv::Ptr<cv::legacy::Tracker>* tracker_algorithm, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->addTarget(*image, *boundingBox, *tracker_algorithm);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_MultiTracker_Alt_update_const__InputArrayR(cv::legacy::MultiTracker_Alt* instance, const cv::_InputArray* image, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->update(*image);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

int cv_legacy_MultiTracker_Alt_propTargetNum_const(const cv::legacy::MultiTracker_Alt* instance) {
		int ret = instance->targetNum;
		return ret;
}

void cv_legacy_MultiTracker_Alt_propTargetNum_const_int(cv::legacy::MultiTracker_Alt* instance, const int val) {
		instance->targetNum = val;
}

std::vector<cv::Ptr<cv::legacy::Tracker>>* cv_legacy_MultiTracker_Alt_propTrackers_const(const cv::legacy::MultiTracker_Alt* instance) {
		std::vector<cv::Ptr<cv::legacy::Tracker>> ret = instance->trackers;
		return new std::vector<cv::Ptr<cv::legacy::Tracker>>(ret);
}

void cv_legacy_MultiTracker_Alt_propTrackers_const_vectorLPtrLTrackerGG(cv::legacy::MultiTracker_Alt* instance, const std::vector<cv::Ptr<cv::legacy::Tracker>>* val) {
		instance->trackers = *val;
}

std::vector<cv::Rect2d>* cv_legacy_MultiTracker_Alt_propBoundingBoxes_const(const cv::legacy::MultiTracker_Alt* instance) {
		std::vector<cv::Rect2d> ret = instance->boundingBoxes;
		return new std::vector<cv::Rect2d>(ret);
}

void cv_legacy_MultiTracker_Alt_propBoundingBoxes_const_vectorLRect2dG(cv::legacy::MultiTracker_Alt* instance, const std::vector<cv::Rect2d>* val) {
		instance->boundingBoxes = *val;
}

std::vector<cv::Scalar>* cv_legacy_MultiTracker_Alt_propColors_const(const cv::legacy::MultiTracker_Alt* instance) {
		std::vector<cv::Scalar> ret = instance->colors;
		return new std::vector<cv::Scalar>(ret);
}

void cv_legacy_MultiTracker_Alt_propColors_const_vectorLScalarG(cv::legacy::MultiTracker_Alt* instance, const std::vector<cv::Scalar>* val) {
		instance->colors = *val;
}

void cv_legacy_MultiTracker_Alt_delete(cv::legacy::MultiTracker_Alt* instance) {
		delete instance;
}

void cv_legacy_Tracker_init_const__InputArrayR_const_Rect2dR(cv::legacy::Tracker* instance, const cv::_InputArray* image, const cv::Rect2d* boundingBox, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->init(*image, *boundingBox);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_Tracker_update_const__InputArrayR_Rect2dR(cv::legacy::Tracker* instance, const cv::_InputArray* image, cv::Rect2d* boundingBox, Result<bool>* ocvrs_return) {
	try {
		bool ret = instance->update(*image, *boundingBox);
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_Tracker_read_const_FileNodeR(cv::legacy::Tracker* instance, const cv::FileNode* fn, ResultVoid* ocvrs_return) {
	try {
		instance->read(*fn);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_Tracker_write_const_FileStorageR(const cv::legacy::Tracker* instance, cv::FileStorage* fs, ResultVoid* ocvrs_return) {
	try {
		instance->write(*fs);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::legacy::TrackerBoosting* cv_legacy_Tracker_to_Legacy_TrackerBoosting(cv::legacy::Tracker* instance) {
		return dynamic_cast<cv::legacy::TrackerBoosting*>(instance);
}

cv::legacy::TrackerCSRT* cv_legacy_Tracker_to_Legacy_TrackerCSRT(cv::legacy::Tracker* instance) {
		return dynamic_cast<cv::legacy::TrackerCSRT*>(instance);
}

cv::legacy::TrackerKCF* cv_legacy_Tracker_to_Legacy_TrackerKCF(cv::legacy::Tracker* instance) {
		return dynamic_cast<cv::legacy::TrackerKCF*>(instance);
}

cv::legacy::TrackerMIL* cv_legacy_Tracker_to_Legacy_TrackerMIL(cv::legacy::Tracker* instance) {
		return dynamic_cast<cv::legacy::TrackerMIL*>(instance);
}

cv::legacy::TrackerMOSSE* cv_legacy_Tracker_to_Legacy_TrackerMOSSE(cv::legacy::Tracker* instance) {
		return dynamic_cast<cv::legacy::TrackerMOSSE*>(instance);
}

cv::legacy::TrackerMedianFlow* cv_legacy_Tracker_to_Legacy_TrackerMedianFlow(cv::legacy::Tracker* instance) {
		return dynamic_cast<cv::legacy::TrackerMedianFlow*>(instance);
}

cv::legacy::TrackerTLD* cv_legacy_Tracker_to_Legacy_TrackerTLD(cv::legacy::Tracker* instance) {
		return dynamic_cast<cv::legacy::TrackerTLD*>(instance);
}

cv::Algorithm* cv_legacy_Tracker_to_Algorithm(cv::legacy::Tracker* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

void cv_legacy_Tracker_delete(cv::legacy::Tracker* instance) {
		delete instance;
}

void cv_legacy_TrackerBoosting_create_const_ParamsR(const cv::legacy::TrackerBoosting::Params* parameters, Result<cv::Ptr<cv::legacy::TrackerBoosting>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerBoosting> ret = cv::legacy::TrackerBoosting::create(*parameters);
		Ok(new cv::Ptr<cv::legacy::TrackerBoosting>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerBoosting_create(Result<cv::Ptr<cv::legacy::TrackerBoosting>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerBoosting> ret = cv::legacy::TrackerBoosting::create();
		Ok(new cv::Ptr<cv::legacy::TrackerBoosting>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Algorithm* cv_legacy_TrackerBoosting_to_Algorithm(cv::legacy::TrackerBoosting* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

cv::legacy::Tracker* cv_legacy_TrackerBoosting_to_Legacy_Tracker(cv::legacy::TrackerBoosting* instance) {
		return dynamic_cast<cv::legacy::Tracker*>(instance);
}

void cv_legacy_TrackerBoosting_delete(cv::legacy::TrackerBoosting* instance) {
		delete instance;
}

void cv_legacy_TrackerBoosting_Params_Params(Result<cv::legacy::TrackerBoosting::Params*>* ocvrs_return) {
	try {
		cv::legacy::TrackerBoosting::Params* ret = new cv::legacy::TrackerBoosting::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerBoosting_Params_read_const_FileNodeR(cv::legacy::TrackerBoosting::Params* instance, const cv::FileNode* fn, ResultVoid* ocvrs_return) {
	try {
		instance->read(*fn);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerBoosting_Params_write_const_FileStorageR(const cv::legacy::TrackerBoosting::Params* instance, cv::FileStorage* fs, ResultVoid* ocvrs_return) {
	try {
		instance->write(*fs);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

int cv_legacy_TrackerBoosting_Params_propNumClassifiers_const(const cv::legacy::TrackerBoosting::Params* instance) {
		int ret = instance->numClassifiers;
		return ret;
}

void cv_legacy_TrackerBoosting_Params_propNumClassifiers_const_int(cv::legacy::TrackerBoosting::Params* instance, const int val) {
		instance->numClassifiers = val;
}

float cv_legacy_TrackerBoosting_Params_propSamplerOverlap_const(const cv::legacy::TrackerBoosting::Params* instance) {
		float ret = instance->samplerOverlap;
		return ret;
}

void cv_legacy_TrackerBoosting_Params_propSamplerOverlap_const_float(cv::legacy::TrackerBoosting::Params* instance, const float val) {
		instance->samplerOverlap = val;
}

float cv_legacy_TrackerBoosting_Params_propSamplerSearchFactor_const(const cv::legacy::TrackerBoosting::Params* instance) {
		float ret = instance->samplerSearchFactor;
		return ret;
}

void cv_legacy_TrackerBoosting_Params_propSamplerSearchFactor_const_float(cv::legacy::TrackerBoosting::Params* instance, const float val) {
		instance->samplerSearchFactor = val;
}

int cv_legacy_TrackerBoosting_Params_propIterationInit_const(const cv::legacy::TrackerBoosting::Params* instance) {
		int ret = instance->iterationInit;
		return ret;
}

void cv_legacy_TrackerBoosting_Params_propIterationInit_const_int(cv::legacy::TrackerBoosting::Params* instance, const int val) {
		instance->iterationInit = val;
}

int cv_legacy_TrackerBoosting_Params_propFeatureSetNumFeatures_const(const cv::legacy::TrackerBoosting::Params* instance) {
		int ret = instance->featureSetNumFeatures;
		return ret;
}

void cv_legacy_TrackerBoosting_Params_propFeatureSetNumFeatures_const_int(cv::legacy::TrackerBoosting::Params* instance, const int val) {
		instance->featureSetNumFeatures = val;
}

void cv_legacy_TrackerBoosting_Params_delete(cv::legacy::TrackerBoosting::Params* instance) {
		delete instance;
}

void cv_legacy_TrackerCSRT_create_const_ParamsR(const cv::legacy::TrackerCSRT::Params* parameters, Result<cv::Ptr<cv::legacy::TrackerCSRT>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerCSRT> ret = cv::legacy::TrackerCSRT::create(*parameters);
		Ok(new cv::Ptr<cv::legacy::TrackerCSRT>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerCSRT_create(Result<cv::Ptr<cv::legacy::TrackerCSRT>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerCSRT> ret = cv::legacy::TrackerCSRT::create();
		Ok(new cv::Ptr<cv::legacy::TrackerCSRT>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerCSRT_setInitialMask_const__InputArrayR(cv::legacy::TrackerCSRT* instance, const cv::_InputArray* mask, ResultVoid* ocvrs_return) {
	try {
		instance->setInitialMask(*mask);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Algorithm* cv_legacy_TrackerCSRT_to_Algorithm(cv::legacy::TrackerCSRT* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

cv::legacy::Tracker* cv_legacy_TrackerCSRT_to_Legacy_Tracker(cv::legacy::TrackerCSRT* instance) {
		return dynamic_cast<cv::legacy::Tracker*>(instance);
}

void cv_legacy_TrackerCSRT_delete(cv::legacy::TrackerCSRT* instance) {
		delete instance;
}

void cv_legacy_TrackerCSRT_Params_read_const_FileNodeR(cv::legacy::TrackerCSRT::Params* instance, const cv::FileNode* unnamed, ResultVoid* ocvrs_return) {
	try {
		instance->read(*unnamed);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerCSRT_Params_write_const_FileStorageR(const cv::legacy::TrackerCSRT::Params* instance, cv::FileStorage* fs, ResultVoid* ocvrs_return) {
	try {
		instance->write(*fs);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::legacy::TrackerCSRT::Params* cv_legacy_TrackerCSRT_Params_defaultNew_const() {
		cv::legacy::TrackerCSRT::Params* ret = new cv::legacy::TrackerCSRT::Params();
		return ret;
}

cv::TrackerCSRT::Params* cv_legacy_TrackerCSRT_Params_to_TrackerCSRT_Params(cv::legacy::TrackerCSRT::Params* instance) {
		return dynamic_cast<cv::TrackerCSRT::Params*>(instance);
}

void cv_legacy_TrackerCSRT_Params_delete(cv::legacy::TrackerCSRT::Params* instance) {
		delete instance;
}

void cv_legacy_TrackerKCF_setFeatureExtractor_void__X__const_cv_Mat__const_cv_Rect__cv_MatR__bool(cv::legacy::TrackerKCF* instance, void (*unnamed)(const cv::Mat, const cv::Rect, cv::Mat&), bool pca_func, ResultVoid* ocvrs_return) {
	try {
		instance->setFeatureExtractor(unnamed, pca_func);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerKCF_setFeatureExtractor_void__X__const_cv_Mat__const_cv_Rect__cv_MatR_(cv::legacy::TrackerKCF* instance, void (*unnamed)(const cv::Mat, const cv::Rect, cv::Mat&), ResultVoid* ocvrs_return) {
	try {
		instance->setFeatureExtractor(unnamed);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerKCF_create_const_ParamsR(const cv::legacy::TrackerKCF::Params* parameters, Result<cv::Ptr<cv::legacy::TrackerKCF>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerKCF> ret = cv::legacy::TrackerKCF::create(*parameters);
		Ok(new cv::Ptr<cv::legacy::TrackerKCF>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerKCF_create(Result<cv::Ptr<cv::legacy::TrackerKCF>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerKCF> ret = cv::legacy::TrackerKCF::create();
		Ok(new cv::Ptr<cv::legacy::TrackerKCF>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Algorithm* cv_legacy_TrackerKCF_to_Algorithm(cv::legacy::TrackerKCF* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

cv::legacy::Tracker* cv_legacy_TrackerKCF_to_Legacy_Tracker(cv::legacy::TrackerKCF* instance) {
		return dynamic_cast<cv::legacy::Tracker*>(instance);
}

void cv_legacy_TrackerKCF_delete(cv::legacy::TrackerKCF* instance) {
		delete instance;
}

void cv_legacy_TrackerKCF_Params_read_const_FileNodeR(cv::legacy::TrackerKCF::Params* instance, const cv::FileNode* unnamed, ResultVoid* ocvrs_return) {
	try {
		instance->read(*unnamed);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerKCF_Params_write_const_FileStorageR(const cv::legacy::TrackerKCF::Params* instance, cv::FileStorage* unnamed, ResultVoid* ocvrs_return) {
	try {
		instance->write(*unnamed);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::legacy::TrackerKCF::Params* cv_legacy_TrackerKCF_Params_defaultNew_const() {
		cv::legacy::TrackerKCF::Params* ret = new cv::legacy::TrackerKCF::Params();
		return ret;
}

void cv_legacy_TrackerKCF_Params_delete(cv::legacy::TrackerKCF::Params* instance) {
		delete instance;
}

void cv_legacy_TrackerMIL_create_const_ParamsR(const cv::legacy::TrackerMIL::Params* parameters, Result<cv::Ptr<cv::legacy::TrackerMIL>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerMIL> ret = cv::legacy::TrackerMIL::create(*parameters);
		Ok(new cv::Ptr<cv::legacy::TrackerMIL>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerMIL_create(Result<cv::Ptr<cv::legacy::TrackerMIL>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerMIL> ret = cv::legacy::TrackerMIL::create();
		Ok(new cv::Ptr<cv::legacy::TrackerMIL>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Algorithm* cv_legacy_TrackerMIL_to_Algorithm(cv::legacy::TrackerMIL* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

cv::legacy::Tracker* cv_legacy_TrackerMIL_to_Legacy_Tracker(cv::legacy::TrackerMIL* instance) {
		return dynamic_cast<cv::legacy::Tracker*>(instance);
}

void cv_legacy_TrackerMIL_delete(cv::legacy::TrackerMIL* instance) {
		delete instance;
}

void cv_legacy_TrackerMIL_Params_read_const_FileNodeR(cv::legacy::TrackerMIL::Params* instance, const cv::FileNode* fn, ResultVoid* ocvrs_return) {
	try {
		instance->read(*fn);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerMIL_Params_write_const_FileStorageR(const cv::legacy::TrackerMIL::Params* instance, cv::FileStorage* fs, ResultVoid* ocvrs_return) {
	try {
		instance->write(*fs);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::legacy::TrackerMIL::Params* cv_legacy_TrackerMIL_Params_defaultNew_const() {
		cv::legacy::TrackerMIL::Params* ret = new cv::legacy::TrackerMIL::Params();
		return ret;
}

void cv_legacy_TrackerMIL_Params_delete(cv::legacy::TrackerMIL::Params* instance) {
		delete instance;
}

void cv_legacy_TrackerMOSSE_create(Result<cv::Ptr<cv::legacy::TrackerMOSSE>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerMOSSE> ret = cv::legacy::TrackerMOSSE::create();
		Ok(new cv::Ptr<cv::legacy::TrackerMOSSE>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Algorithm* cv_legacy_TrackerMOSSE_to_Algorithm(cv::legacy::TrackerMOSSE* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

cv::legacy::Tracker* cv_legacy_TrackerMOSSE_to_Legacy_Tracker(cv::legacy::TrackerMOSSE* instance) {
		return dynamic_cast<cv::legacy::Tracker*>(instance);
}

void cv_legacy_TrackerMOSSE_delete(cv::legacy::TrackerMOSSE* instance) {
		delete instance;
}

void cv_legacy_TrackerMedianFlow_create_const_ParamsR(const cv::legacy::TrackerMedianFlow::Params* parameters, Result<cv::Ptr<cv::legacy::TrackerMedianFlow>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerMedianFlow> ret = cv::legacy::TrackerMedianFlow::create(*parameters);
		Ok(new cv::Ptr<cv::legacy::TrackerMedianFlow>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerMedianFlow_create(Result<cv::Ptr<cv::legacy::TrackerMedianFlow>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerMedianFlow> ret = cv::legacy::TrackerMedianFlow::create();
		Ok(new cv::Ptr<cv::legacy::TrackerMedianFlow>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Algorithm* cv_legacy_TrackerMedianFlow_to_Algorithm(cv::legacy::TrackerMedianFlow* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

cv::legacy::Tracker* cv_legacy_TrackerMedianFlow_to_Legacy_Tracker(cv::legacy::TrackerMedianFlow* instance) {
		return dynamic_cast<cv::legacy::Tracker*>(instance);
}

void cv_legacy_TrackerMedianFlow_delete(cv::legacy::TrackerMedianFlow* instance) {
		delete instance;
}

void cv_legacy_TrackerMedianFlow_Params_Params(Result<cv::legacy::TrackerMedianFlow::Params*>* ocvrs_return) {
	try {
		cv::legacy::TrackerMedianFlow::Params* ret = new cv::legacy::TrackerMedianFlow::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerMedianFlow_Params_read_const_FileNodeR(cv::legacy::TrackerMedianFlow::Params* instance, const cv::FileNode* unnamed, ResultVoid* ocvrs_return) {
	try {
		instance->read(*unnamed);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerMedianFlow_Params_write_const_FileStorageR(const cv::legacy::TrackerMedianFlow::Params* instance, cv::FileStorage* unnamed, ResultVoid* ocvrs_return) {
	try {
		instance->write(*unnamed);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

int cv_legacy_TrackerMedianFlow_Params_propPointsInGrid_const(const cv::legacy::TrackerMedianFlow::Params* instance) {
		int ret = instance->pointsInGrid;
		return ret;
}

void cv_legacy_TrackerMedianFlow_Params_propPointsInGrid_const_int(cv::legacy::TrackerMedianFlow::Params* instance, const int val) {
		instance->pointsInGrid = val;
}

void cv_legacy_TrackerMedianFlow_Params_propWinSize_const(const cv::legacy::TrackerMedianFlow::Params* instance, cv::Size* ocvrs_return) {
		cv::Size ret = instance->winSize;
		*ocvrs_return = ret;
}

void cv_legacy_TrackerMedianFlow_Params_propWinSize_const_Size(cv::legacy::TrackerMedianFlow::Params* instance, const cv::Size* val) {
		instance->winSize = *val;
}

int cv_legacy_TrackerMedianFlow_Params_propMaxLevel_const(const cv::legacy::TrackerMedianFlow::Params* instance) {
		int ret = instance->maxLevel;
		return ret;
}

void cv_legacy_TrackerMedianFlow_Params_propMaxLevel_const_int(cv::legacy::TrackerMedianFlow::Params* instance, const int val) {
		instance->maxLevel = val;
}

void cv_legacy_TrackerMedianFlow_Params_propTermCriteria_const(const cv::legacy::TrackerMedianFlow::Params* instance, cv::TermCriteria* ocvrs_return) {
		cv::TermCriteria ret = instance->termCriteria;
		*ocvrs_return = ret;
}

void cv_legacy_TrackerMedianFlow_Params_propTermCriteria_const_TermCriteria(cv::legacy::TrackerMedianFlow::Params* instance, const cv::TermCriteria* val) {
		instance->termCriteria = *val;
}

void cv_legacy_TrackerMedianFlow_Params_propWinSizeNCC_const(const cv::legacy::TrackerMedianFlow::Params* instance, cv::Size* ocvrs_return) {
		cv::Size ret = instance->winSizeNCC;
		*ocvrs_return = ret;
}

void cv_legacy_TrackerMedianFlow_Params_propWinSizeNCC_const_Size(cv::legacy::TrackerMedianFlow::Params* instance, const cv::Size* val) {
		instance->winSizeNCC = *val;
}

double cv_legacy_TrackerMedianFlow_Params_propMaxMedianLengthOfDisplacementDifference_const(const cv::legacy::TrackerMedianFlow::Params* instance) {
		double ret = instance->maxMedianLengthOfDisplacementDifference;
		return ret;
}

void cv_legacy_TrackerMedianFlow_Params_propMaxMedianLengthOfDisplacementDifference_const_double(cv::legacy::TrackerMedianFlow::Params* instance, const double val) {
		instance->maxMedianLengthOfDisplacementDifference = val;
}

void cv_legacy_TrackerMedianFlow_Params_delete(cv::legacy::TrackerMedianFlow::Params* instance) {
		delete instance;
}

void cv_legacy_TrackerTLD_create_const_ParamsR(const cv::legacy::TrackerTLD::Params* parameters, Result<cv::Ptr<cv::legacy::TrackerTLD>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerTLD> ret = cv::legacy::TrackerTLD::create(*parameters);
		Ok(new cv::Ptr<cv::legacy::TrackerTLD>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerTLD_create(Result<cv::Ptr<cv::legacy::TrackerTLD>*>* ocvrs_return) {
	try {
		cv::Ptr<cv::legacy::TrackerTLD> ret = cv::legacy::TrackerTLD::create();
		Ok(new cv::Ptr<cv::legacy::TrackerTLD>(ret), ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

cv::Algorithm* cv_legacy_TrackerTLD_to_Algorithm(cv::legacy::TrackerTLD* instance) {
		return dynamic_cast<cv::Algorithm*>(instance);
}

cv::legacy::Tracker* cv_legacy_TrackerTLD_to_Legacy_Tracker(cv::legacy::TrackerTLD* instance) {
		return dynamic_cast<cv::legacy::Tracker*>(instance);
}

void cv_legacy_TrackerTLD_delete(cv::legacy::TrackerTLD* instance) {
		delete instance;
}

void cv_legacy_TrackerTLD_Params_Params(Result<cv::legacy::TrackerTLD::Params*>* ocvrs_return) {
	try {
		cv::legacy::TrackerTLD::Params* ret = new cv::legacy::TrackerTLD::Params();
		Ok(ret, ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerTLD_Params_read_const_FileNodeR(cv::legacy::TrackerTLD::Params* instance, const cv::FileNode* unnamed, ResultVoid* ocvrs_return) {
	try {
		instance->read(*unnamed);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerTLD_Params_write_const_FileStorageR(const cv::legacy::TrackerTLD::Params* instance, cv::FileStorage* unnamed, ResultVoid* ocvrs_return) {
	try {
		instance->write(*unnamed);
		Ok(ocvrs_return);
	} OCVRS_CATCH(ocvrs_return);
}

void cv_legacy_TrackerTLD_Params_delete(cv::legacy::TrackerTLD::Params* instance) {
		delete instance;
}

}
