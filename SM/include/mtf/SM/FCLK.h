#ifndef MTF_FCLK_H
#define MTF_FCLK_H

#include "SearchMethod.h"
#include "FCLKParams.h"

_MTF_BEGIN_NAMESPACE

template<class AM, class SSM>
class FCLK : public SearchMethod < AM, SSM > {
public:

	typedef FCLKParams ParamType;
	typedef ParamType::HessType HessType;

	using SearchMethod<AM, SSM> ::am;
	using SearchMethod<AM, SSM> ::ssm;
	using typename SearchMethod<AM, SSM> ::AMParams;
	using typename SearchMethod<AM, SSM> ::SSMParams;
	using SearchMethod<AM, SSM> ::cv_corners_mat;
	using SearchMethod<AM, SSM> ::name;
	using SearchMethod<AM, SSM> ::initialize;
	using SearchMethod<AM, SSM> ::update;	

	FCLK(const ParamType *fclk_params = nullptr,
		const AMParams *am_params = nullptr, const SSMParams *ssm_params = nullptr);

	void initialize(const cv::Mat &corners) override;
	void update() override;
	void setRegion(const cv::Mat& corners) override;

protected:
	ParamType params;

	// Let S = size of SSM state vector and N = resx * resy = no. of pixels in the object patch

	//! 1 x S Jacobian of the appearance model w.r.t. SSM state vector
	RowVectorXd df_dp;
	//! S x S Hessian of the appearance model w.r.t. SSM state vector
	MatrixXd d2f_dp2, init_d2f_dp2;
	//! N x S jacobians of the pix values w.r.t the SSM state vector 
	MatrixXd dI0_dpssm, dIt_dpssm;

	//! N x S x S hessians of the pixel values w.r.t the SSM state vector stored as a (S*S) x N 2D matrix
	MatrixXd d2I0_dpssm2, d2It_dpssm2;

	Matrix24d prev_corners;

	VectorXd state_update, ssm_update, am_update;
	VectorXd inv_ssm_update, inv_am_update;

	int state_size, ssm_state_size, am_state_size;

	int frame_id;

	init_profiling();
	char *log_fname;
	char *time_fname;
};



_MTF_END_NAMESPACE

#endif

