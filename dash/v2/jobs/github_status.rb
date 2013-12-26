require 'httparty'

GITHUB_STATUS_TO_TRAFFIC_LIGHT_MAP = {
  'good' => 'green',
  'minor' => 'amber',
  'major' => 'red'
}
GITHUB_STATUS_URI = 'https://status.github.com/api/last-message.json'
GITHUB_STATUS_EVENT_ID = 'github_status'

SCHEDULER.every '1m', :first_in => 0 do
                response = HTTParty.get(GITHUB_STATUS_URI)
                data = {
                     status: GITHUB_STATUS_TO_TRAFFIC_LIGHT_MAP[response["status"]],
                     message: response["body"]
                }
                send_event(GITHUB_STATUS_EVENT_ID, data)
end
