#include "util.hpp"

#include "duckdb/common/assert.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb/common/unordered_set.hpp"
#include "duckdb/storage/block.hpp"

namespace duckdb {

string FormatPercentage(idx_t blocks, idx_t total_blocks) {
	if (total_blocks == 0) {
		return "0.0%";
	}
	const double pct = static_cast<double>(blocks) * 100.0 / static_cast<double>(total_blocks);
	return StringUtil::Format("%.1f%%", pct);
}

idx_t CountUniqueBlocks(const vector<ColumnSegmentInfo> &segment_info) {
	unordered_set<block_id_t> unique_blocks;

	for (const auto &seg : segment_info) {
		if (seg.persistent && seg.block_id != INVALID_BLOCK) {
			unique_blocks.insert(seg.block_id);
			for (const auto &block_id : seg.additional_blocks) {
				D_ASSERT(block_id != INVALID_BLOCK);
				unique_blocks.insert(block_id);
			}
		}
	}

	return unique_blocks.size();
}

} // namespace duckdb
