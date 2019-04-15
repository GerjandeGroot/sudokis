	component test is
		port (
			clk_clk             : in    std_logic                     := 'X';             -- clk
			reset_reset_n       : in    std_logic                     := 'X';             -- reset_n
			vga_connector_CLK   : out   std_logic;                                        -- CLK
			vga_connector_HS    : out   std_logic;                                        -- HS
			vga_connector_VS    : out   std_logic;                                        -- VS
			vga_connector_BLANK : out   std_logic;                                        -- BLANK
			vga_connector_SYNC  : out   std_logic;                                        -- SYNC
			vga_connector_R     : out   std_logic_vector(7 downto 0);                     -- R
			vga_connector_G     : out   std_logic_vector(7 downto 0);                     -- G
			vga_connector_B     : out   std_logic_vector(7 downto 0);                     -- B
			pixel_buffer_DQ     : inout std_logic_vector(15 downto 0) := (others => 'X'); -- DQ
			pixel_buffer_ADDR   : out   std_logic_vector(19 downto 0);                    -- ADDR
			pixel_buffer_LB_N   : out   std_logic;                                        -- LB_N
			pixel_buffer_UB_N   : out   std_logic;                                        -- UB_N
			pixel_buffer_CE_N   : out   std_logic;                                        -- CE_N
			pixel_buffer_OE_N   : out   std_logic;                                        -- OE_N
			pixel_buffer_WE_N   : out   std_logic                                         -- WE_N
		);
	end component test;

	u0 : component test
		port map (
			clk_clk             => CONNECTED_TO_clk_clk,             --           clk.clk
			reset_reset_n       => CONNECTED_TO_reset_reset_n,       --         reset.reset_n
			vga_connector_CLK   => CONNECTED_TO_vga_connector_CLK,   -- vga_connector.CLK
			vga_connector_HS    => CONNECTED_TO_vga_connector_HS,    --              .HS
			vga_connector_VS    => CONNECTED_TO_vga_connector_VS,    --              .VS
			vga_connector_BLANK => CONNECTED_TO_vga_connector_BLANK, --              .BLANK
			vga_connector_SYNC  => CONNECTED_TO_vga_connector_SYNC,  --              .SYNC
			vga_connector_R     => CONNECTED_TO_vga_connector_R,     --              .R
			vga_connector_G     => CONNECTED_TO_vga_connector_G,     --              .G
			vga_connector_B     => CONNECTED_TO_vga_connector_B,     --              .B
			pixel_buffer_DQ     => CONNECTED_TO_pixel_buffer_DQ,     --  pixel_buffer.DQ
			pixel_buffer_ADDR   => CONNECTED_TO_pixel_buffer_ADDR,   --              .ADDR
			pixel_buffer_LB_N   => CONNECTED_TO_pixel_buffer_LB_N,   --              .LB_N
			pixel_buffer_UB_N   => CONNECTED_TO_pixel_buffer_UB_N,   --              .UB_N
			pixel_buffer_CE_N   => CONNECTED_TO_pixel_buffer_CE_N,   --              .CE_N
			pixel_buffer_OE_N   => CONNECTED_TO_pixel_buffer_OE_N,   --              .OE_N
			pixel_buffer_WE_N   => CONNECTED_TO_pixel_buffer_WE_N    --              .WE_N
		);

