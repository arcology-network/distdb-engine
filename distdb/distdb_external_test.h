#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	void distdb_basic_wr_test();
	void distdb_320_byte_x_1m_entries_batch_wr_test();
	void distdb_320_byte_x_50m_entries_batch_wr_test();
	void distdb_320_byte_x_50m_entries_batch_r_test();

	void distdb_batch_write_1m_test();

#ifdef __cplusplus
}
#endif
