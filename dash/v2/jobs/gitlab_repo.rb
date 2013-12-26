#!/usr/bin/env ruby
require 'net/http'
require 'json'


gitlab_token = "YOUR TOKEN"
gitlab_uri = "URL GITLAB"
# number of repositories to display in the list
# order the list by the numbers
ordered = true

SCHEDULER.every '3m', :first_in => 0 do |job|
  uri = URI("#{gitlab_uri}api/v3/projects?private_token=#{gitlab_token}")
  response = Net::HTTP.get(uri)
  data = JSON.parse(response)
  result = Array.new
  data.each do |app|
    uri2 = URI("#{gitlab_uri}api/v3/projects/#{app["id"]}/issues?private_token=#{gitlab_token}")
    response2 = Net::HTTP.get(uri2)
    data2 = JSON.parse(response2)
    compteur = 0
    data2.each do |issue|
      if issue["state"] == "opened"
        compteur += 1
      end
    end
     result.push({
       label: app["name"],
       value: compteur
     })
  end
  if ordered
    result = result.sort_by { |obj| -obj[:value] }
  end
  send_event('gitlab_repo', { items: result})
end # SCHEDULER
