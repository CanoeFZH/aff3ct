#ifndef FACTORY_ENCODER_TURBO_HPP
#define FACTORY_ENCODER_TURBO_HPP

#include <string>

#include "Module/Interleaver/Interleaver.hpp"
#include "Module/Encoder/Encoder.hpp"
#include "Module/Encoder/Encoder_sys.hpp"

#include "Tools/Factory/Module/Factory_interleaver.hpp"

#include "../Factory_encoder.hpp"

namespace aff3ct
{
namespace tools
{
struct Factory_encoder_turbo : public Factory_encoder
{
	struct parameters : Factory_encoder::parameters
	{
		virtual ~parameters() {}

		bool buffered = true;
		std::string json_path = "";

		// ------- code
		std::string      standard;
		std::vector<int> poly        = {013, 015};
		int              tail_length = 4 * 3;
		int              N_pct;

		typename Factory_interleaver::parameters itl;
	};

	template <typename B = int>
	static module::Encoder<B>* build(const parameters               &params,
	                                 const module::Interleaver<int> &itl,
	                                       module::Encoder_sys<B>   *enc_n,
	                                       module::Encoder_sys<B>   *enc_i = nullptr);

	static void build_args(Arguments_reader::arg_map &req_args, Arguments_reader::arg_map &opt_args);
	static void store_args(const Arguments_reader& ar, parameters &params,
	                       const int K, const int N, const int n_frames = 1);
	static void group_args(Arguments_reader::arg_grp& ar);

	static void header(params_list& head_enc, params_list& head_cde, params_list& head_itl, const parameters& params);
};
}
}

#endif /* FACTORY_ENCODER_TURBO_HPP */