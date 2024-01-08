#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/select/select.h"
#include "esphome/components/pipsolar/select/pipsolar_select.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace pipsolar {
class PipsolarSelect;

enum ENUMPollingCommand {
  POLLING_QPIRI = 0,
  POLLING_QPIGS = 1,
  POLLING_QPIGS2 = 2,
  POLLING_QMOD = 3,
  // POLLING_QFLAG = 4,
  // POLLING_QPIWS = 5,
  // POLLING_QT = 6,
  // POLLING_QMN = 7,
  // POLLING_QBATCD = 8,
  // POLLING_QET = 9,
  // POLLING_QLT = 10,
  // POLLING_QMCHGCR = 11,
  // POLLING_QMUCHGCR = 12,
  POLLING_QPGS0 = 13,
  // POLLING_Q1 = 14,
  // POLLING_QBMS = 15,
};
struct PollingCommand {
  uint8_t *command;
  uint8_t length = 0;
  uint8_t errors;
  ENUMPollingCommand identifier;
};

#define PIPSOLAR_VALUED_ENTITY_(type, name, polling_command, value_type) \
 protected: \
  value_type value_##name##_; \
  PIPSOLAR_ENTITY_(type, name, polling_command)

#define PIPSOLAR_ENTITY_(type, name, polling_command) \
 protected: \
  type *name##_{}; /* NOLINT */ \
\
 public: \
  void set_##name(type *name) { /* NOLINT */ \
    this->name##_ = name; \
    this->add_polling_command_(#polling_command, POLLING_##polling_command); \
  }

#define PIPSOLAR_SENSOR(name, polling_command, value_type) \
  PIPSOLAR_VALUED_ENTITY_(sensor::Sensor, name, polling_command, value_type)
#define PIPSOLAR_SWITCH(name, polling_command) PIPSOLAR_ENTITY_(switch_::Switch, name, polling_command)
#define PIPSOLAR_SELECT(name, polling_command) PIPSOLAR_ENTITY_(pipsolar::PipsolarSelect, name, polling_command)
#define PIPSOLAR_VALUED_SELECT(name, polling_command, value_type) \
  PIPSOLAR_VALUED_ENTITY_(pipsolar::PipsolarSelect, name, polling_command, value_type)
#define PIPSOLAR_BINARY_SENSOR(name, polling_command, value_type) \
  PIPSOLAR_VALUED_ENTITY_(binary_sensor::BinarySensor, name, polling_command, value_type)
#define PIPSOLAR_VALUED_TEXT_SENSOR(name, polling_command, value_type) \
  PIPSOLAR_VALUED_ENTITY_(text_sensor::TextSensor, name, polling_command, value_type)
#define PIPSOLAR_TEXT_SENSOR(name, polling_command) PIPSOLAR_ENTITY_(text_sensor::TextSensor, name, polling_command)

class Pipsolar : public uart::UARTDevice, public PollingComponent {
  // QPIGS values
  PIPSOLAR_SENSOR(grid_voltage, QPIGS, float)
  PIPSOLAR_SENSOR(grid_frequency, QPIGS, float)
  PIPSOLAR_SENSOR(ac_output_voltage, QPIGS, float)
  PIPSOLAR_SENSOR(ac_output_frequency, QPIGS, float)
  PIPSOLAR_SENSOR(ac_output_apparent_power, QPIGS, int)
  PIPSOLAR_SENSOR(ac_output_active_power, QPIGS, int)
  PIPSOLAR_SENSOR(output_load_percent, QPIGS, int)
  PIPSOLAR_SENSOR(bus_voltage, QPIGS, int)
  PIPSOLAR_SENSOR(battery_voltage, QPIGS, float)
  PIPSOLAR_SENSOR(battery_charging_current, QPIGS, int)
  PIPSOLAR_SENSOR(battery_capacity_percent, QPIGS, int)
  PIPSOLAR_SENSOR(inverter_heat_sink_temperature, QPIGS, int)
  PIPSOLAR_SENSOR(pv1_input_current, QPIGS, float)
  PIPSOLAR_SENSOR(pv1_input_voltage, QPIGS, float)
  PIPSOLAR_SENSOR(battery_voltage_scc, QPIGS, float)
  PIPSOLAR_SENSOR(battery_discharge_current, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(add_sbu_priority_version, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(configuration_status, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(scc_firmware_version, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(load_status, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(battery_voltage_to_steady_while_charging, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(charging_status, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(scc_charging_status, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(ac_charging_status, QPIGS, int)
  PIPSOLAR_SENSOR(battery_voltage_offset_for_fans_on, QPIGS, int)  //.1 scale
  PIPSOLAR_SENSOR(eeprom_version, QPIGS, int)
  PIPSOLAR_SENSOR(pv1_charging_power, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(charging_to_floating_mode, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(switch_on, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(dustproof_installed, QPIGS, int)
  PIPSOLAR_BINARY_SENSOR(solar_feed_to_grid_status, QPIWS, bool)
  PIPSOLAR_SENSOR(solar_feed_to_grid_power, QPIWS, char)
  PIPSOLAR_SENSOR(country_customized_regulation, QPIWS, int)

  // QPIGS2 values

  PIPSOLAR_SENSOR(pv2_input_current, QPIGS2, float)
  PIPSOLAR_SENSOR(pv2_input_voltage, QPIGS2, float)
  PIPSOLAR_SENSOR(pv2_charging_power, QPIGS2, int)

  // QPGS0 values

  PIPSOLAR_BINARY_SENSOR(parallel_num_0, QPGS0, bool)
  PIPSOLAR_SENSOR(serial_number_0, QPGS0, long)
  PIPSOLAR_VALUED_TEXT_SENSOR(work_mode_0, QPGS0, char)
  PIPSOLAR_SENSOR(fault_code_0, QPGS0, int)
  PIPSOLAR_SENSOR(grid_voltage_0, QPGS0, float)
  PIPSOLAR_SENSOR(grid_frequency_0, QPGS0, float)
  PIPSOLAR_SENSOR(ac_output_voltage_0, QPGS0, float)
  PIPSOLAR_SENSOR(ac_output_frequency_0, QPGS0, float)
  PIPSOLAR_SENSOR(ac_output_apparent_power_0, QPGS0, int)
  PIPSOLAR_SENSOR(ac_output_active_power_0, QPGS0, int)
  PIPSOLAR_SENSOR(load_percent_0, QPGS0, int)
  PIPSOLAR_SENSOR(battery_voltage_0, QPGS0, float)
  PIPSOLAR_SENSOR(battery_charging_current_0, QPGS0, int)
  PIPSOLAR_SENSOR(battery_capacity_0, QPGS0, int)
  PIPSOLAR_SENSOR(pv1_input_voltage_0, QPGS0, float)
  PIPSOLAR_SENSOR(total_charging_current_0, QPGS0, int)
  PIPSOLAR_SENSOR(total_ac_output_apparent_power_0, QPGS0, int)
  PIPSOLAR_SENSOR(total_output_active_power_0, QPGS0, int)
  PIPSOLAR_SENSOR(total_ac_output_percentage_0, QPGS0, int)
  PIPSOLAR_BINARY_SENSOR(inverter_status_scc_0, QPGS0, bool)
  PIPSOLAR_BINARY_SENSOR(inverter_status_ac_charging_0, QPGS0, bool)
  PIPSOLAR_BINARY_SENSOR(inverter_status_scc_charging_0, QPGS0, bool)
  PIPSOLAR_SENSOR(inverter_status_battery_0, QPGS0, int)
  PIPSOLAR_BINARY_SENSOR(inverter_status_line_0, QPGS0, bool)
  PIPSOLAR_BINARY_SENSOR(inverter_status_load_0, QPGS0, bool)
  PIPSOLAR_BINARY_SENSOR(inverter_status_configuration_0, QPGS0, bool)
  PIPSOLAR_SENSOR(output_mode_0, QPGS0, int)
  PIPSOLAR_SENSOR(charger_source_priority_0, QPGS0, int)
  PIPSOLAR_SENSOR(max_charger_current_0, QPGS0, int)
  PIPSOLAR_SENSOR(max_charger_range_0, QPGS0, int)
  PIPSOLAR_SENSOR(max_ac_charger_current_0, QPGS0, int)
  PIPSOLAR_SENSOR(pv1_input_current_0, QPGS0, int)
  PIPSOLAR_SENSOR(battery_discharge_current_0, QPGS0, int)
  PIPSOLAR_SENSOR(pv2_input_voltage_0, QPGS0, float)
  PIPSOLAR_SENSOR(pv2_input_current_0, QPGS0, int)

  // QPIRI values
  PIPSOLAR_SENSOR(grid_rating_voltage, QPIRI, float)
  PIPSOLAR_SENSOR(grid_rating_current, QPIRI, float)
  PIPSOLAR_SENSOR(ac_output_rating_voltage, QPIRI, float)
  PIPSOLAR_SENSOR(ac_output_rating_frequency, QPIRI, float)
  PIPSOLAR_SENSOR(ac_output_rating_current, QPIRI, float)
  PIPSOLAR_SENSOR(ac_output_rating_apparent_power, QPIRI, int)
  PIPSOLAR_SENSOR(ac_output_rating_active_power, QPIRI, int)
  PIPSOLAR_SENSOR(battery_rating_voltage, QPIRI, float)
  PIPSOLAR_SENSOR(battery_recharge_voltage, QPIRI, float)
  PIPSOLAR_SENSOR(battery_under_voltage, QPIRI, float)
  PIPSOLAR_SENSOR(battery_bulk_voltage, QPIRI, float)
  PIPSOLAR_SENSOR(battery_float_voltage, QPIRI, float)
  PIPSOLAR_SENSOR(battery_type, QPIRI, int)
  PIPSOLAR_SENSOR(current_max_ac_charging_current, QPIRI, int)
  PIPSOLAR_SENSOR(current_max_charging_current, QPIRI, int)
  PIPSOLAR_SENSOR(input_voltage_range, QPIRI, int)
  PIPSOLAR_SENSOR(output_source_priority, QPIRI, int)
  PIPSOLAR_SENSOR(charger_source_priority, QPIRI, int)
  PIPSOLAR_SENSOR(parallel_max_num, QPIRI, int)
  PIPSOLAR_SENSOR(machine_type, QPIRI, int)
  PIPSOLAR_SENSOR(topology, QPIRI, int)
  PIPSOLAR_SENSOR(output_mode, QPIRI, int)
  PIPSOLAR_SENSOR(battery_redischarge_voltage, QPIRI, float)
  PIPSOLAR_SENSOR(pv_ok_condition_for_parallel, QPIRI, int)
  PIPSOLAR_SENSOR(pv_power_balance, QPIRI, int)
  PIPSOLAR_SENSOR(max_charging_time_at_cv_stage, QPIRI, int)
  PIPSOLAR_VALUED_TEXT_SENSOR(operation_logic, QPIRI, std::string)
  PIPSOLAR_SENSOR(max_discharging_current, QPIRI, int)

  // QMOD values
  PIPSOLAR_VALUED_TEXT_SENSOR(device_mode, QMOD, char)

  // QFLAG values
  PIPSOLAR_BINARY_SENSOR(silence_buzzer_open_buzzer, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(overload_bypass_function, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(lcd_escape_to_default, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(overload_restart_function, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(over_temperature_restart_function, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(backlight_on, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(alarm_on_when_primary_source_interrupt, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(fault_code_record, QFLAG, int)
  PIPSOLAR_BINARY_SENSOR(power_saving, QFLAG, int)

  // QPIWS values
  PIPSOLAR_BINARY_SENSOR(warnings_present, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(faults_present, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_power_loss, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_fault, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_bus_over, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_bus_under, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_bus_soft_fail, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_line_fail, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_opvshort, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_voltage_too_low, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_voltage_too_high, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_over_temperature, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_fan_lock, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_voltage_high, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_low_alarm, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_under_shutdown, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_derating, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_over_load, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_eeprom_failed, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_over_current, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_inverter_soft_failed, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_self_test_failed, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_op_dc_voltage_over, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_battery_open, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_current_sensor_failed, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_battery_short, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_power_limit, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_pv_voltage_high, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_mppt_overload, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_mppt_overload, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_too_low_to_charge, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(fault_dc_dc_over_current, QPIWS, bool)
  PIPSOLAR_SENSOR(fault_code, QPIWS, int)
  PIPSOLAR_BINARY_SENSOR(warning_battery_weak, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_high_ac_input_during_bus_soft_start, QPIWS, bool)
  PIPSOLAR_BINARY_SENSOR(warning_battery_equalization, QPIWS, bool)

  // QBATCD values
  PIPSOLAR_BINARY_SENSOR(discharge_onoff, QBATCD, bool)
  PIPSOLAR_BINARY_SENSOR(discharge_with_standby_onoff, QBATCD, bool)
  PIPSOLAR_BINARY_SENSOR(charge_onoff, QBATCD, bool)
  
  PIPSOLAR_VALUED_TEXT_SENSOR(inverter_date, QT, std::string)
  PIPSOLAR_VALUED_TEXT_SENSOR(inverter_time, QT, std::string)

  PIPSOLAR_TEXT_SENSOR(last_qpigs, QPIGS)
  PIPSOLAR_TEXT_SENSOR(last_qpigs2, QPIGS2)
  PIPSOLAR_TEXT_SENSOR(last_qpgs0, QPGS0)
  PIPSOLAR_TEXT_SENSOR(last_qpiri, QPIRI)
  PIPSOLAR_TEXT_SENSOR(last_qmod, QMOD)
  PIPSOLAR_TEXT_SENSOR(last_qflag, QFLAG)
  PIPSOLAR_TEXT_SENSOR(last_qpiws, QPIWS)
  PIPSOLAR_TEXT_SENSOR(last_qt, QT)
  PIPSOLAR_TEXT_SENSOR(last_qmn, QMN)
  PIPSOLAR_TEXT_SENSOR(last_qet, QET)
  PIPSOLAR_TEXT_SENSOR(last_qlt, QLT)
  PIPSOLAR_TEXT_SENSOR(last_qbatcd, QBATCD)
  PIPSOLAR_TEXT_SENSOR(last_qmchgcr, QMCHGCR)
  PIPSOLAR_TEXT_SENSOR(last_qmuchgcr, QMUCHGCR)
  PIPSOLAR_TEXT_SENSOR(last_q1, Q1)
  PIPSOLAR_TEXT_SENSOR(last_qbms, QBMS)

  PIPSOLAR_SENSOR(total_pv_generated_energy, QET, int)

  PIPSOLAR_SENSOR(total_output_load_energy, QLT, int)

  PIPSOLAR_SWITCH(output_source_priority_utility_switch, QPIRI)
  PIPSOLAR_SWITCH(output_source_priority_solar_switch, QPIRI)
  PIPSOLAR_SWITCH(output_source_priority_battery_switch, QPIRI)
  PIPSOLAR_SWITCH(input_voltage_range_switch, QPIRI)
  PIPSOLAR_SWITCH(pv_ok_condition_for_parallel_switch, QPIRI)
  PIPSOLAR_SWITCH(pv_power_balance_switch, QPIRI)

  PIPSOLAR_SELECT(output_source_priority_select, QPIRI)
  PIPSOLAR_SELECT(charger_source_priority_select, QPIRI)
  
  PIPSOLAR_SELECT(current_max_ac_charging_current_select, QPIRI)
  PIPSOLAR_SELECT(current_max_charging_current_select, QPIRI)
  
  PIPSOLAR_VALUED_SELECT(charging_discharging_control_select, QBATCD, std::string)

  PIPSOLAR_SELECT(battery_type_select, QPIRI)
  PIPSOLAR_SELECT(battery_recharge_voltage_select, QPIRI)
  PIPSOLAR_SELECT(battery_redischarge_voltage_select, QPIRI)
  PIPSOLAR_SELECT(battery_cutoff_voltage_select, QPIRI)
  PIPSOLAR_SELECT(battery_bulk_voltage_select, QPIRI)
  PIPSOLAR_SELECT(battery_float_voltage_select, QPIRI)
  PIPSOLAR_SELECT(battery_max_bulk_charging_time_select, QPIRI)
  PIPSOLAR_SELECT(max_discharging_current_select, QPIRI)
  PIPSOLAR_VALUED_SELECT(bms_values_select, QBMS, std::string)

  // Q1
  PIPSOLAR_SENSOR(time_until_absorb_charging, Q1, int)
  PIPSOLAR_SENSOR(time_until_float_charging, Q1, int)
  PIPSOLAR_BINARY_SENSOR(scc_flag, Q1, int)
  PIPSOLAR_BINARY_SENSOR(allow_scc_on, Q1, int)
  PIPSOLAR_SENSOR(charge_average_current, Q1, int)
  PIPSOLAR_SENSOR(scc_pwm_temperature, Q1, int)
  PIPSOLAR_SENSOR(inverter_temperature, Q1, int)
  PIPSOLAR_SENSOR(battery_temperature, Q1, int)
  PIPSOLAR_SENSOR(transformer_temperature, Q1, int)
  PIPSOLAR_BINARY_SENSOR(fan_lock_status, Q1, int)
  PIPSOLAR_SENSOR(fan_pwm_speed, Q1, int)
  PIPSOLAR_SENSOR(scc_charge_power, Q1, int)
  PIPSOLAR_BINARY_SENSOR(parallel_warning, Q1, int)
  PIPSOLAR_SENSOR(sync_frequency, Q1, float)
  PIPSOLAR_VALUED_TEXT_SENSOR(inverter_charge_status, Q1, std::string)

  void switch_command(const std::string &command);
  void setup() override;
  void loop() override;
  void dump_config() override;
  void update() override;

 protected:
  friend class PipsolarSelect;
  static const size_t PIPSOLAR_READ_BUFFER_LENGTH = 160;  // maximum supported answer length
  static const size_t COMMAND_QUEUE_LENGTH = 20;
  static const size_t COMMAND_TIMEOUT = 5000;
  uint32_t last_poll_ = 0;
  void add_polling_command_(const char *command, ENUMPollingCommand polling_command);
  void empty_uart_buffer_();
  uint8_t check_incoming_crc_();
  uint8_t check_incoming_length_(uint8_t length);
  uint16_t cal_crc_half_(uint8_t *msg, uint8_t len);
  uint8_t send_next_command_();
  void send_next_poll_();
  void queue_command_(const char *command, uint8_t length);
  std::string command_queue_[COMMAND_QUEUE_LENGTH];
  uint8_t command_queue_position_ = 0;
  uint8_t read_buffer_[PIPSOLAR_READ_BUFFER_LENGTH];
  size_t read_pos_{0};

  uint32_t command_start_millis_ = 0;
  uint8_t state_;
  enum State {
    STATE_IDLE = 0,
    STATE_POLL = 1,
    STATE_COMMAND = 2,
    STATE_POLL_COMPLETE = 3,
    STATE_COMMAND_COMPLETE = 4,
    STATE_POLL_CHECKED = 5,
    STATE_POLL_DECODED = 6,
  };

  uint8_t last_polling_command_ = 0;
  PollingCommand used_polling_commands_[15];
};

}  // namespace pipsolar
}  // namespace esphome
