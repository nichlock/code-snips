-- File to handle all the C VPI functions
-- Include with:
-- use work.vpi_c_functions.all;

library IEEE;
use IEEE.Std_Logic_1164.all;

package c_vpi_functions is

  procedure init_c_prog (config: in integer);
    attribute foreign of init_c_prog :
      procedure is "VHPIDIRECT init_c_prog";

  procedure clock_wait (xx: in integer);
    attribute foreign of clock_wait :
      procedure is "VHPIDIRECT clock_wait";

	procedure timer_start (sim_time: in delay_length; ignoreRepeats: in integer);
		attribute foreign of timer_start :
			procedure is "VHPIDIRECT timer_start";

	procedure timer_stop (sim_time: in delay_length; ignoreRepeats: in integer);
		attribute foreign of timer_stop :
			procedure is "VHPIDIRECT timer_stop";

  procedure clock_count (sim_now: in delay_length);
    attribute foreign of clock_count :
      procedure is "VHPIDIRECT clock_count";

  procedure print_8_bit (reg: in integer; sim_now: in delay_length);
    attribute foreign of print_8_bit :
      procedure is "VHPIDIRECT print_8_bit";

end c_vpi_functions;

package body c_vpi_functions is

  procedure init_c_prog (config: in integer) is
  begin
    assert false report "VHPI" severity failure;
  end init_c_prog;

  procedure clock_wait (xx: in integer) is
  begin
    assert false report "VHPI" severity failure;
  end clock_wait;

  procedure timer_start (sim_time: in delay_length; ignoreRepeats: in integer) is
  begin
    assert false report "VHPI" severity failure;
  end timer_start;

  procedure timer_stop (sim_time: in delay_length; ignoreRepeats: in integer) is
  begin
    assert false report "VHPI" severity failure;
  end timer_stop;

  procedure clock_count (sim_now: in delay_length) is
  begin
    assert false report "VHPI" severity failure;
  end clock_count;

  procedure print_8_bit (reg: in integer; sim_now: in delay_length) is
  begin
    assert false report "VHPI" severity failure;
  end print_8_bit;

end c_vpi_functions;
