
module test (
	clk_clk,
	reset_reset_n,
	vga_connector_CLK,
	vga_connector_HS,
	vga_connector_VS,
	vga_connector_BLANK,
	vga_connector_SYNC,
	vga_connector_R,
	vga_connector_G,
	vga_connector_B,
	pixel_buffer_DQ,
	pixel_buffer_ADDR,
	pixel_buffer_LB_N,
	pixel_buffer_UB_N,
	pixel_buffer_CE_N,
	pixel_buffer_OE_N,
	pixel_buffer_WE_N);	

	input		clk_clk;
	input		reset_reset_n;
	output		vga_connector_CLK;
	output		vga_connector_HS;
	output		vga_connector_VS;
	output		vga_connector_BLANK;
	output		vga_connector_SYNC;
	output	[7:0]	vga_connector_R;
	output	[7:0]	vga_connector_G;
	output	[7:0]	vga_connector_B;
	inout	[15:0]	pixel_buffer_DQ;
	output	[19:0]	pixel_buffer_ADDR;
	output		pixel_buffer_LB_N;
	output		pixel_buffer_UB_N;
	output		pixel_buffer_CE_N;
	output		pixel_buffer_OE_N;
	output		pixel_buffer_WE_N;
endmodule
