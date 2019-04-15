	test u0 (
		.clk_clk             (<connected-to-clk_clk>),             //           clk.clk
		.reset_reset_n       (<connected-to-reset_reset_n>),       //         reset.reset_n
		.vga_connector_CLK   (<connected-to-vga_connector_CLK>),   // vga_connector.CLK
		.vga_connector_HS    (<connected-to-vga_connector_HS>),    //              .HS
		.vga_connector_VS    (<connected-to-vga_connector_VS>),    //              .VS
		.vga_connector_BLANK (<connected-to-vga_connector_BLANK>), //              .BLANK
		.vga_connector_SYNC  (<connected-to-vga_connector_SYNC>),  //              .SYNC
		.vga_connector_R     (<connected-to-vga_connector_R>),     //              .R
		.vga_connector_G     (<connected-to-vga_connector_G>),     //              .G
		.vga_connector_B     (<connected-to-vga_connector_B>),     //              .B
		.pixel_buffer_DQ     (<connected-to-pixel_buffer_DQ>),     //  pixel_buffer.DQ
		.pixel_buffer_ADDR   (<connected-to-pixel_buffer_ADDR>),   //              .ADDR
		.pixel_buffer_LB_N   (<connected-to-pixel_buffer_LB_N>),   //              .LB_N
		.pixel_buffer_UB_N   (<connected-to-pixel_buffer_UB_N>),   //              .UB_N
		.pixel_buffer_CE_N   (<connected-to-pixel_buffer_CE_N>),   //              .CE_N
		.pixel_buffer_OE_N   (<connected-to-pixel_buffer_OE_N>),   //              .OE_N
		.pixel_buffer_WE_N   (<connected-to-pixel_buffer_WE_N>)    //              .WE_N
	);

