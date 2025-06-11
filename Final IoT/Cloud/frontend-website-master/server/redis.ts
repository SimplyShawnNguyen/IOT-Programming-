import { createClient } from 'redis'

const client = createClient({ url: 'redis://default@172.20.10.13:6379' })
client.on('error', (error) => {
    console.error(`Redis client error:`, error)
})

const connected = Promise.all([client.connect()])

export async function getRedisClient() {
    await connected

    return client
}
